#include "glfw/Window.hpp"

#include "Acorn/Core/Assert.hpp"

namespace GLFW
{
    Window::Window(WindowDescriptor descriptor)
        : m_logger(descriptor.moduleLogger)
    {
        if (!glfwInit())
        {
            // throw error
            // ACORN_ASSERT(false && "Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(
            descriptor.width,
            descriptor.height,
            descriptor.title.c_str(),
            nullptr, nullptr);
        
        if (!m_window)
        {
            glfwTerminate();
            ACORN_ASSERT(false && "Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_window);
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
}
