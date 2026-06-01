#include <chrono>

#include "Acorn/Threading/JobScheduler.hpp"

using namespace std::chrono;

namespace Acorn::Threading
{
    JobScheduler::JobScheduler(JobSchedulerDescriptor desc)
        : m_logger(desc.loggerFactory.create("JobScheduler")),
          m_workerThreads{},
          m_jobsQueue{},
          m_callbacksQueue{},
          m_jobsMutex{},
          m_callbacksMutex{},
          m_sleepCondition{},
          m_workerThreadsCount{
              desc.workerThreadsCount == 0
              ? std::thread::hardware_concurrency() - 1
              : desc.workerThreadsCount},
          m_maxCallbacksPerFrame{desc.maxCallbacksPerFrame},
          m_frameCallbackBudget_ms{desc.frameCallbackBudget_ms}
    {
        // TODO: Get rid of that duplicate call to hardware_concurrency()
        const size_t maxWorkerThreadsCount = std::thread::hardware_concurrency() - 1;

        if (m_workerThreadsCount > maxWorkerThreadsCount)
        {
            m_logger.warn(
                "The number of requested worker threads ({}) exceeds the maximum allowed on this machine ({})",
                m_workerThreadsCount,
                maxWorkerThreadsCount
            );
            // m_logger.warn("If you wish to disable this limit: <TODO>");
            m_workerThreadsCount = maxWorkerThreadsCount;
            m_logger.warn("Worker threads count lowered to {}", m_workerThreadsCount);
        };

        spawnWorkerThreads(m_workerThreadsCount);
    }

    void JobScheduler::update()
    {
        executeCallbacksBudgeted();
    }

    void JobScheduler::shutdown()
    {
        shutdownWorkerThreads();
        executeAllCallbacks();
    }

    void JobScheduler::scheduleJob(Job job)
    {
        std::unique_lock<std::mutex> lock(m_jobsMutex);
        m_jobsQueue.push(job);
        lock.unlock();

        m_sleepCondition.notify_one();
    }

    void JobScheduler::spawnWorkerThreads(size_t workersCount)
    {
        if (!m_workerThreads.isEmpty())
        {
            m_logger.warn("Destroying existing threads");
            shutdownWorkerThreads();
        }

        m_workerThreads.setCapacity(workersCount);

        for (size_t i = 0; i < workersCount; i++)
        {
            WorkerThreadDescriptor descriptor
            {
                .jobsQueue           = m_jobsQueue,
                .callbacksQueue      = m_callbacksQueue,
                .jobsQueueMutex      = m_jobsMutex,
                .callbacksQueueMutex = m_callbacksMutex,
                .sleepCondition      = m_sleepCondition,
            };

            m_workerThreads.emplace(descriptor);

            m_logger.info(
                "Created worker thread {}/{}",
                i + 1,
                workersCount
            );
        }
    }

    void JobScheduler::shutdownWorkerThreads()
    {
        for (auto& worker: m_workerThreads)
            worker.stop();

        m_sleepCondition.notify_all();

        for (size_t i = 0; i < m_workerThreads.getSize(); i++)
        {
            m_workerThreads[i].join();
            m_logger.info("Shutdown worker thread {}/{}", i + 1, m_workerThreads.getSize());
        }

        m_workerThreads.clearAll();
    }

    void JobScheduler::executeCallbacksBudgeted()
    {
        std::unique_lock<std::mutex> lock{m_callbacksMutex};

        if (m_callbacksQueue.empty())
        {
            lock.unlock();
            return;
        }
        lock.unlock();
       
        const auto start = high_resolution_clock::now();

        for (uint32_t i = 0;
             i < std::min(m_maxCallbacksPerFrame, static_cast<uint32_t>(m_callbacksQueue.size()));
             i++)
        {
            lock.lock();
            const Job job = m_callbacksQueue.back();
            m_callbacksQueue.pop();

            job.callback(job.data);
            lock.unlock();

            const auto duration = duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - start);
            if (duration.count() >= m_frameCallbackBudget_ms)
                break;
        }
    }

    void JobScheduler::executeAllCallbacks()
    {
        std::unique_lock<std::mutex> lock{m_callbacksMutex};

        for (size_t i = 0; i < m_callbacksQueue.size(); i++)
        {
            Job job = m_callbacksQueue.back();
            m_callbacksQueue.pop();

            job.callback(job.data);
        }

        lock.unlock();
    }
}
