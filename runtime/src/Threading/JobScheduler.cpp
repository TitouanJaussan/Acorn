#include <chrono>

#include "Acorn/Threading/JobScheduler.hpp"
#include "Acorn/Base/DetailedError.hpp"
#include "Acorn/Threading/WorkerThread.hpp"

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
          m_maxCallbacksPerFrame{desc.maxCallbacksPerFrame},
          m_frameCallbackBudget_ms{desc.frameCallbackBudget_ms}
    {}

    void JobScheduler::update()
    {
        executeCallbacksBudgeted();
    }

    void JobScheduler::shutdown()
    {
        shutdownWorkerThreads();
        executeAllCallbacks();
    }

    void JobScheduler::submitJob(Job job)
    {
        std::unique_lock<std::mutex> lock(m_jobsMutex);
        m_jobsQueue.push(job);
        lock.unlock();

        m_sleepCondition.notify_one();
    }

    void JobScheduler::spawnWorkerThreads(ThreadingManager& threadingManager,
        size_t workersCount)
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
                .threadingManager    = threadingManager,
                .jobsQueue           = m_jobsQueue,
                .callbacksQueue      = m_callbacksQueue,
                .jobsQueueMutex      = m_jobsMutex,
                .callbacksQueueMutex = m_callbacksMutex,
                .sleepCondition      = m_sleepCondition,
            };

            try
            {
                m_workerThreads.append(
                    UniquePtr<WorkerThread>::create(
                        std::move(descriptor)));

                m_logger.info(
                    "Created worker thread {}/{}",
                    i + 1,
                    workersCount
                );
            }
            catch (const Base::DetailedError& err)
            {
                m_logger.error(
                    "Failed to create worker thread: {}",
                    err.what());
            }
        }
    }

    void JobScheduler::shutdownWorkerThreads()
    {
        for (auto& worker: m_workerThreads)
            worker->stop();

        m_sleepCondition.notify_all();

        for (size_t i = 0; i < m_workerThreads.getSize(); i++)
        {
            m_workerThreads[i]->join();
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
