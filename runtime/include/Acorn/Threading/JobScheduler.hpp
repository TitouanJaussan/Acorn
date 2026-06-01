#ifndef ACORN_JOB_SCHEDULER_HPP
#define ACORN_JOB_SCHEDULER_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Threading/JobSchedulerDescriptor.hpp"
#include "Acorn/Threading/WorkerThread.hpp"
#include "Acorn/Threading/Job.hpp"

namespace Acorn::Threading
{
    // TODO: Refactor this class, it does too much on it's own
    class ENGINE_API JobScheduler
    {
    public:
        JobScheduler(JobSchedulerDescriptor descriptor);

        void update();
        void shutdown();

        void scheduleJob(Job job);

    private:
        void spawnWorkerThreads(size_t workersCount);
        void shutdownWorkerThreads();
        void executeCallbacksBudgeted();
        void executeAllCallbacks();  // What is the purpose of this ?
        
        Core::Logger m_logger;

        ArrayList<WorkerThread> m_workerThreads;

        std::queue<Job> m_jobsQueue;
        std::queue<Job> m_callbacksQueue;

        std::mutex m_jobsMutex;
        std::mutex m_callbacksMutex;

        std::condition_variable m_sleepCondition;

        size_t m_workerThreadsCount;
        const uint32_t m_maxCallbacksPerFrame;
        const float m_frameCallbackBudget_ms;
    };
}

#endif /* ACORN_JOB_SCHEDULER_HPP */
