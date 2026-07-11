#include "RenderService.hpp"
#include "WindowModule/API.hpp"
#include <GL/gl.h>

using namespace std::chrono_literals;

RenderService::RenderService(Acorn::Base::LoggerFactory& factory,
    Acorn::Module::APIHandle& windowModAPI)
    : Acorn::Threading::Service(Acorn::Threading::ServiceDescriptor
        {
            .name = "Render",
            .factory = factory
        }),
      m_windowModAPI(windowModAPI)
{}

void RenderService::work()
{
    m_logger.info("Starting Render Service!");

    m_windowModAPI.as<WindowModuleAPI>()
        ->getMainWindow()
        ->makeContextCurrent();

    const auto size = m_windowModAPI.as<WindowModuleAPI>()
        ->getMainWindow()
        ->getSize();

    glViewport(0, 0, size.m_first, size.m_second);

    while (m_running)
    {
        glClearColor(0.9, 0.6, 0.8, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_windowModAPI.as<WindowModuleAPI>()
            ->getMainWindow()
            ->swapBuffers();

        std::this_thread::sleep_for(.1s);
    }

    m_windowModAPI.as<WindowModuleAPI>()
        ->getMainWindow()
        ->releaseCurrentContext();
    m_logger.info("Stopped Render Service!");
}
