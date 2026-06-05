#ifndef ACORN_JOB_SCHEDULER_HPP
#define ACORN_JOB_SCHEDULER_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Threading/JobSchedulerDescriptor.hpp"
#include "Acorn/Threading/WorkerThread.hpp"
#include "Acorn/Threading/Job.hpp"

namespace Acorn::Threading
{
    // TODO: Maybe refactor this class, it does too much on it's own
    class ENGINE_API JobScheduler
    {
    public:
        JobScheduler(JobSchedulerDescriptor descriptor);

        void update();
        void shutdown();

        void scheduleJob(Job job);

        void spawnWorkerThreads(ThreadingManager& threadingManager,
            size_t workersCount);

    private:
        void shutdownWorkerThreads();
        void executeCallbacksBudgeted();
        void executeAllCallbacks();
        
        Core::Logger m_logger;

        ArrayList<UniquePtr<WorkerThread>> m_workerThreads;

        std::queue<Job> m_jobsQueue;
        std::queue<Job> m_callbacksQueue;

        std::mutex m_jobsMutex;
        std::mutex m_callbacksMutex;

        std::condition_variable m_sleepCondition;

        const uint32_t m_maxCallbacksPerFrame;
        const float m_frameCallbackBudget_ms;
    };
}

#endif /* ACORN_JOB_SCHEDULER_HPP */
