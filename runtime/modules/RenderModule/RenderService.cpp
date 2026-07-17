#include <GL/gl.h>

#include "RenderService.hpp"
#include "WindowModule/API.hpp"
#include "SceneModule/API.hpp"

using namespace std::chrono_literals;

RenderService::RenderService(
        Acorn::Base::LoggerFactory& factory,
        Acorn::Module::APIHandle<> windowModAPI,
        Acorn::Module::APIHandle<> sceneModAPI)
    : Acorn::Threading::Service(Acorn::Threading::ServiceDescriptor
        {
            .name = "Render",
            .factory = factory
        }),
      m_windowModAPI(windowModAPI),
      m_sceneModAPI(sceneModAPI)
{}

void RenderService::work()
{
    m_logger.info("Starting Render Service!");

    m_windowModAPI->getMainWindow()->makeContextCurrent();

    const Acorn::Math::Vec2i size = m_windowModAPI
        ->getMainWindow()
        ->getSize();

    glViewport(0, 0, size.x(), size.y());
    m_logger.info("Set viewport dimensions to: {}", size);

    while (m_running)
    {
        glClearColor(0.9, 0.6, 0.8, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Retrieve render data from the scene
        m_sceneModAPI->getRenderDataSnapshot();
        m_windowModAPI->getMainWindow()->swapBuffers();

        std::this_thread::sleep_for(.5s);
    }

    m_windowModAPI->getMainWindow()->releaseCurrentContext();

    m_logger.info("Stopped Render Service!");
}
