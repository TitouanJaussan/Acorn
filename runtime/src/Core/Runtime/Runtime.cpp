#include "Acorn/Core/Runtime/Runtime.hpp"

#include "Acorn/Core/Memory/Tracker.hpp"
#include "Acorn/Version/RuntimeVersion.hpp"
#include "Core/SignalHandler.hpp"

namespace Acorn::Core
{
    Runtime::Runtime(int argc, const char** argv)
        : m_version(RUNTIME_VERSION_MAJOR,
                    RUNTIME_VERSION_MINOR,
                    RUNTIME_VERSION_PATCH),
          m_running(true),
          m_loggerFactory("log.tmp"),
          m_logger(m_loggerFactory.create("Runtime")),

          m_filesystem(m_loggerFactory, std::filesystem::absolute(argv[0]).parent_path()),
          m_threadingManager(m_loggerFactory),
          m_layerManager(m_loggerFactory),
          m_modManager(m_loggerFactory)
    {
        init(argc, argv);
        logRuntimeInfo();

        m_modManager.loadModules("modules/", m_filesystem, createAPI());
    }

    Runtime::~Runtime()
    {
        m_logger.info("Shutting down runtime...");

        m_threadingManager.m_jobScheduler.shutdown();

        m_logger.info("Maximum memory usage reached: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
        m_logger.info("Total memory usage: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
    }

    void Runtime::init(int argc, const char** argv)
    {
        setSignalHandler(this);
    }

    void Runtime::run()
    {
        m_modManager.callInit(*this);  // I don't like this

        while (m_running)
        {
            m_modManager.callUpdate();
           m_threadingManager.update();
        }

        m_threadingManager.shutdown();
        m_modManager.callUnload();
    }

    void Runtime::stop()
    {
        m_running = false;
    }

    LoggerFactory& Runtime::getLoggerFactory() noexcept
    {
        return m_loggerFactory;
    }

    Threading::ThreadingManager& Runtime::getThreadingManager() noexcept
    {
        return m_threadingManager;
    }

    Module::ModuleManager& Runtime::getModuleManager() noexcept
    {
        return m_modManager;
    }

    RuntimeAPI Runtime::createAPI()
    {
        return RuntimeAPI{*this, m_version};
    }

    void Runtime::logRuntimeInfo()
    {
        m_logger.info(
            "Initialized Acorn Engine runtime {}",
            m_version.string()
        );
    }
}
