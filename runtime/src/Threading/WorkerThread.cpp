#include <mutex>

#include "Acorn/Threading/WorkerThread.hpp"

namespace Acorn::Threading
{
    WorkerThread::WorkerThread(WorkerThreadDescriptor desc)
        : m_jobsQueue(desc.jobsQueue),
          m_callbacksQueue(desc.callbacksQueue),
          m_jobsQueueMutex(desc.jobsQueueMutex),
          m_callbacksQueueMutex(desc.callbacksQueueMutex),
          m_sleepCondition(desc.sleepCondition),
          m_thread([&]() -> void { work(); }),
          m_running(true)
    {}

    WorkerThread::WorkerThread(WorkerThread&& other)
        : m_jobsQueue(other.m_jobsQueue),
          m_callbacksQueue(other.m_callbacksQueue),
          m_jobsQueueMutex(other.m_jobsQueueMutex),
          m_callbacksQueueMutex(other.m_callbacksQueueMutex),
          m_sleepCondition(other.m_sleepCondition),
          m_thread(std::move(other.m_thread)),
          m_running(other.m_running.load())
    {}

    void WorkerThread::stop()
    {
        m_running = false;
    }

    void WorkerThread::join()
    {
        if (m_thread.joinable())
            m_thread.join();
    }

    void WorkerThread::work()
    {
        m_running = true;

        while (m_running)
        {
            std::unique_lock<std::mutex> jobsQueueLock(m_jobsQueueMutex);

            m_sleepCondition.wait(jobsQueueLock, [this]
            {
                return !m_jobsQueue.empty() || !m_running;
            });

            if (!m_running)
                break;

            Job job = m_jobsQueue.front();
            m_jobsQueue.pop();

            jobsQueueLock.unlock();

            job.work(job.data);
            if (job.callback == nullptr)
                continue;

            std::lock_guard<std::mutex> callbacksQueueLock(m_callbacksQueueMutex);
            m_callbacksQueue.push(job);
        }
    }
}
