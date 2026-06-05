#ifndef ACORN_WORKER_THREAD_HPP
#define ACORN_WORKER_THREAD_HPP

#include <thread>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Threading/WorkerThreadDescriptor.hpp"
#include "Acorn/Threading/Job.hpp"

namespace Acorn::Threading
{
    class ENGINE_API WorkerThread
    {
    public:
        WorkerThread(WorkerThreadDescriptor descriptor);

        WorkerThread(WorkerThread&&) = delete;
        WorkerThread(const WorkerThread&) = delete;
        WorkerThread& operator=(WorkerThread&&) = delete;
        WorkerThread& operator=(const WorkerThread&) = delete;

        void stop();
        void join();

    private:
        void work();

        std::queue<Job>& m_jobsQueue;
        std::queue<Job> m_callbacksQueue;

        std::mutex& m_jobsQueueMutex;
        std::mutex& m_callbacksQueueMutex;

        std::condition_variable& m_sleepCondition;

        std::thread m_thread;
        std::atomic_bool m_running;
    };
}

#endif /* ACORN_WORKER_THREAD_HPP */
