#ifndef ACORN_WORKER_THREAD_DESCRIPTOR_HPP
#define ACORN_WORKER_THREAD_DESCRIPTOR_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Threading/Job.hpp"

namespace Acorn::Threading
{
    class ThreadingManager;

    struct ENGINE_API WorkerThreadDescriptor
    {
        ThreadingManager& threadingManager;  // Maybe this should be replaced with smaller, dedicated factory

        std::queue<Job>& jobsQueue;
        std::queue<Job>& callbacksQueue;

        std::mutex& jobsQueueMutex;
        std::mutex& callbacksQueueMutex;

        std::condition_variable& sleepCondition;
    };
}

#endif /* ACORN_WORKER_THREAD_DESCRIPTOR_HPP */
