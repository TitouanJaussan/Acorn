#ifndef ACORN_THREADING_MANAGER_HPP
#define ACORN_THREADING_MANAGER_HPP

#include <cstddef>
#include <thread>
#include <functional>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Logging/Logger.hpp"
#include "Acorn/Threading/JobScheduler.hpp"
#include "Acorn/Threading/ServiceManager.hpp"

namespace Acorn::Threading
{
    class ENGINE_API ThreadingManager
    {
    public:
        ThreadingManager(Core::LoggerFactory& factory);

        std::thread queryNewThread(std::function<void()> fn);
        void update();
        void shutdown();
        
        const size_t m_maxThreadsCount;

        JobScheduler m_jobScheduler;
        ServiceManager m_serviceManager;

    private:
        size_t m_threadsCount;
        Core::Logger m_logger;

    };
}

#endif /* ACORN_THREADING_MANAGER_HPP */
