#include "Acorn/Core/Runtime/Engine.hpp"

#include "Acorn/Core/CommandLineArguments/CommandLineArgumentsDescriptor.hpp"
#include "Acorn/Base/Memory/Tracker.hpp"
#include "Core/SignalHandler.hpp"

namespace Acorn::Runtime
{
    Engine::Engine(int argc, char** argv)
        : m_core{"log.tmp"},

          m_cmdLineArgs(Core::CommandLineArgumentsDescriptor
          {
              .factory = m_core.loggerFactory,
              .argc = argc,
              .argv = argv
          }),

          // Probably could rewrite this in a cleaner manner
          m_systems(
              m_core.loggerFactory,
              std::filesystem::path(
                  m_cmdLineArgs.getArgumentOr(
                      "root-dir",
                      String(std::filesystem::absolute(argv[0])
                          .parent_path()
                          .c_str()
                      )
                  ).getData()
              )
          )
    {
        Core::setSignalHandler(this);
        logEngineInfo();

        m_systems.modManager.loadModules(
            "modules/",
            m_systems.filesystem,
            createAPI());
    }

    Engine::~Engine()
    {
        m_core.logger.info("Shutting down runtime...");

        m_systems.threadingManager.m_jobScheduler.shutdown();

        m_core.logger.info("Maximum memory usage reached: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
        m_core.logger.info("Total memory usage: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
    }

    void Engine::run()
    {
        m_systems.modManager.callInit(*this);  // I don't like this

        while (m_core.running)
        {
            m_systems.modManager.callUpdate();
            m_systems.threadingManager.update();
        }

        m_systems.threadingManager.shutdown();
        m_systems.modManager.callUnload();
    }

    void Engine::stop()
    {
        m_core.running = false;
    }

    Base::LoggerFactory& Engine::getLoggerFactory()
    {
        return m_core.loggerFactory;
    }

    API Engine::createAPI()
    {
        return API{*this, m_core.version};
    }

    void Engine::logEngineInfo()
    {
        m_core.logger.info(
            "Initialized Acorn Engine runtime {}",
            m_core.version.string()
        );
    }
}
