#include "RenderService.hpp"
#include "WindowModule/API.hpp"

using namespace std::chrono_literals;

RenderService::RenderService(Acorn::Core::LoggerFactory& factory,
    Acorn::Threading::ThreadingManager& threadingManager,
    Acorn::Module::APIHandle& windowModAPI)
    : Acorn::Threading::Service(Acorn::Threading::ServiceDescriptor
        {
            .name = "Render",
            .factory = factory,
            .threadingManager = threadingManager
        }),
      m_windowModAPI(windowModAPI)
{}

void RenderService::work()
{
    m_logger.info("Starting Render Service!");
    m_windowModAPI.as<WindowModuleAPI>()
        ->getMainWindow()
        ->makeContextCurrent();

    while (m_running)
    {
        std::this_thread::sleep_for(.5s);
    }

    m_windowModAPI.as<WindowModuleAPI>()
        ->getMainWindow()
        ->releaseCurrentContext();
    m_logger.info("Stopped Render Service!");
}
