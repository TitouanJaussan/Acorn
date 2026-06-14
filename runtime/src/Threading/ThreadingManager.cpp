#include <thread>
#include <algorithm>

#include "Acorn/Threading/ThreadingManager.hpp"
#include "Acorn/Threading/JobSchedulerDescriptor.hpp"
#include "Acorn/Threading/ThreadingError.hpp"
#include "Acorn/Core/Format.hpp"

namespace Acorn::Threading
{
    ThreadingManager::ThreadingManager(Core::LoggerFactory& factory)
        : m_maxThreadsCount(
            std::min(4u, std::thread::hardware_concurrency() - 1)),
          m_jobScheduler(JobSchedulerDescriptor{
            .loggerFactory = factory,
            .maxCallbacksPerFrame = 2,
            .frameCallbackBudget_ms = 4.0f
          }),
          m_serviceManager(factory),
          m_threadsCount(0),
          m_logger(factory.create("ThreadingManager"))
    {
        m_logger.info("Max threads count: {}", m_maxThreadsCount);

        m_jobScheduler.spawnWorkerThreads(*this,
            std::min((size_t)4, m_maxThreadsCount - 2));
    }

    std::thread ThreadingManager::queryNewThread(std::function<void()> fn)
    {
        if (m_threadsCount == m_maxThreadsCount)
            throw ThreadingError(Core::format(
                "Can't complete new thread query: maximum simultaneous threads count ({}) reached",
                m_maxThreadsCount
            ));

        m_logger.info("Completed new thread query!");

        ++m_threadsCount;
        return std::thread(std::move(fn));  // That doesn mean that the thread starts executing even
                                            // before it's even returned (realistically it's the same
                                            // as if it started when returned)
    }

    void ThreadingManager::update()
    {
        m_jobScheduler.update();
    }

    void ThreadingManager::shutdown()
    {
        m_jobScheduler.shutdown();
        m_serviceManager.shutdown();
    }
}
