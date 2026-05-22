#include "Acorn/Core/Runtime.hpp"

#include "Window/glfw/Window.hpp"

namespace Acorn::Core
{
    Runtime::Runtime(int argc, const char** argv)
        : m_loggerFactory("log.tmp"),
          m_logger(m_loggerFactory.create("Runtime")),
          m_layerManager(),
          m_modManager(m_loggerFactory),
          m_window(new Window::GLFW::Window(
            Window::GLFW::WindowDescriptor{
                .loggerFactory = m_loggerFactory,
                .title = "Acorn Engine",
                .width = 1200,
                .height = 800
            }))
    {
        // TODO: Make this a proper fix
        std::filesystem::current_path(std::filesystem::absolute(argv[0]).parent_path());

        m_modManager.loadModules("modules/");
        m_modManager.callLoad(m_loggerFactory);
    }

    Runtime::~Runtime()
    {
        m_logger.info("Shutting down runtime...");
    }

    void Runtime::run()
    {
        while (!m_window->shouldClose())
        {
            m_modManager.callUpdate();
            m_window->swapBuffers();
            m_window->pollEvents();
        }

        m_modManager.callUnload();
    }

    LoggerFactory& Runtime::getLoggerFactory() noexcept
    {
        return m_loggerFactory;
    }
}
