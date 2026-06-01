#ifndef ACORN_WORKER_THREAD_DESCRIPTOR_HPP
#define ACORN_WORKER_THREAD_DESCRIPTOR_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Threading/Job.hpp"

namespace Acorn::Threading
{
    struct ENGINE_API WorkerThreadDescriptor
    {
        std::queue<Job>& jobsQueue;
        std::queue<Job>& callbacksQueue;

        std::mutex& jobsQueueMutex;
        std::mutex& callbacksQueueMutex;

        std::condition_variable& sleepCondition;
    };
}

#endif /* ACORN_WORKER_THREAD_DESCRIPTOR_HPP */
