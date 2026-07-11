#include <thread>
#include <algorithm>

#include "Acorn/Threading/ThreadingManager.hpp"
#include "Acorn/Threading/JobSchedulerDescriptor.hpp"
#include "Acorn/Threading/ThreadingError.hpp"
#include "Acorn/Base/Format.hpp"

namespace Acorn::Threading
{
    ThreadingManager::ThreadingManager(Base::LoggerFactory& factory)
        : maxThreadsCount(
              std::min(4u, std::thread::hardware_concurrency() - 1)),
          jobScheduler(JobSchedulerDescriptor
          {
              .loggerFactory = factory,
              .maxCallbacksPerFrame = 2,
              .frameCallbackBudget_ms = 4.0f
          }),
          serviceManager(factory),
          m_threadsCount(0),
          m_logger(factory.create("ThreadingManager"))
    {
        m_logger.info("Max threads count: {}", maxThreadsCount);

        jobScheduler.spawnWorkerThreads(*this,
            std::min((size_t)4, maxThreadsCount - 2));
    }

    std::thread ThreadingManager::queryNewThread(std::function<void()> fn)
    {
        if (m_threadsCount == maxThreadsCount)
            throw ThreadingError(Base::format(
                "Can't complete new thread query: maximum simultaneous threads count ({}) reached",
                maxThreadsCount
            ));

        m_logger.info("Completed thread query");

        ++m_threadsCount;
        return std::thread(std::move(fn));  // That doesn't mean that the thread starts executing even
                                            // before it's even returned (realistically it's the same
                                            // as if it started when returned)
    }

    ThreadingManagerHandle ThreadingManager::newHandle()
    {
        return ThreadingManagerHandle(*this);
    }

    void ThreadingManager::update()
    {
        jobScheduler.update();
    }

    void ThreadingManager::shutdown()
    {
        jobScheduler.shutdown();
        serviceManager.shutdown();
    }
}
