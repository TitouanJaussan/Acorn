#ifndef ACORN_THREADING_MANAGER_HPP
#define ACORN_THREADING_MANAGER_HPP

#include <cstddef>
#include <thread>
#include <functional>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Threading/JobScheduler.hpp"
#include "Acorn/Threading/ServiceManager.hpp"
#include "Acorn/Threading/ThreadingManagerHandle.hpp"

namespace Acorn::Threading
{
    class ENGINE_API ThreadingManager
    {
    public:
        ThreadingManager(Base::LoggerFactory& factory);

        std::thread queryNewThread(std::function<void()> fn);
        ThreadingManagerHandle newHandle();

        void update();
        void shutdown();
        
        const size_t maxThreadsCount;

        JobScheduler jobScheduler;
        ServiceManager serviceManager;

    private:
        size_t m_threadsCount;
        Base::Logger m_logger;

    };
}

#endif /* ACORN_THREADING_MANAGER_HPP */
