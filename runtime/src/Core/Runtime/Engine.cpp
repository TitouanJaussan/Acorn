#include "Acorn/Core/Runtime/Engine.hpp"

#include "Acorn/Core/CommandLineArguments/CommandLineArgumentsDescriptor.hpp"
#include "Acorn/Base/Memory/Tracker.hpp"
#include "Core/SignalHandler.hpp"
#include <cmath>

namespace Acorn::Runtime
{
    Engine::Engine(int argc, char** argv)
        : m_core{"log.tmp"},

          cmdLineArgs(Core::CommandLineArgumentsDescriptor
          {
              .factory = m_core.loggerFactory,
              .argc = argc,
              .argv = argv
          }),

          // Probably could rewrite this in a cleaner manner
          systems(
              m_core.loggerFactory,
              std::filesystem::path(
                  cmdLineArgs.getArgumentOr(
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

        systems.modManager.loadModules(
            "modules/",
            systems.filesystem,
            createAPI());
    }

    Engine::~Engine()
    {
        m_core.logger.info("Shutting down runtime...");

        // Ok this is weird, why doing this manually ??
        systems.threadingManager.jobScheduler.shutdown();

        m_core.logger.info("Maximum memory usage reached: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
        m_core.logger.info("Total memory usage: {} bytes",
            Memory::Tracker::getSingleton()->getMaxMemUsage());
    }

    void Engine::run()
    {
        systems.modManager.callInit(*this);  // I don't like this

        while (m_core.running)
        {
            systems.modManager.callUpdate();
            systems.threadingManager.update();
        }

        systems.threadingManager.shutdown();
        systems.modManager.callUnload();
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
