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
          m_layerManager(),
          m_modManager(m_loggerFactory)
    {
        init(argc, argv);
        logRuntimeInfo();

        m_modManager.loadModules("modules/", m_loggerFactory, createAPI());
        m_modManager.callInit();
    }

    Runtime::~Runtime()
    {
        m_logger.info("Shutting down runtime...");

        m_logger.info("Maximum memory usage reached: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
        m_logger.info("Total memory usage: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
    }

    void Runtime::init(int argc, const char** argv)
    {
        setSignalHandler(this);

        // TODO: Make this a proper fix
        std::filesystem::current_path(std::filesystem::absolute(argv[0]).parent_path());
    }

    void Runtime::run()
    {
        while (m_running)
        {
            m_modManager.callUpdate();
        }

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

    RuntimeAPI Runtime::createAPI()
    {
        return RuntimeAPI{*this, m_version};
    }

    void Runtime::logRuntimeInfo()
    {
        m_logger.info(
            "Acorn Engine runtime {}",
            m_version.string()
        );
    }
}
