#include "Acorn/Core/Runtime/Runtime.hpp"

#include "Core/SignalHandler.hpp"

namespace Acorn::Core
{
    Runtime::Runtime(int argc, const char** argv)
        : m_loggerFactory("log.tmp"),
          m_logger(m_loggerFactory.create("Runtime")),
          m_layerManager(),
          m_modManager(m_loggerFactory),
          m_running(true)
    {
        m_logger.info("Initializing runtime...");

        setSignalHandler(this);

        // TODO: Make this a proper fix
        std::filesystem::current_path(std::filesystem::absolute(argv[0]).parent_path());

        m_modManager.loadModules("modules/", m_loggerFactory, getAPI());
        m_modManager.callInit();
    }

    Runtime::~Runtime()
    {
        m_logger.info("Shutting down runtime...");
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

    RuntimeAPI Runtime::getAPI()
    {
        return RuntimeAPI{*this};
    }
}
