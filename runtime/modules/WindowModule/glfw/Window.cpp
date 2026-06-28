#include "glfw/Window.hpp"

#include <Acorn/Core/Assert.hpp>
#include <Acorn/Core/DetailedError.hpp>

namespace GLFW
{
    Window::Window(WindowDescriptor desc)
        : m_logger(desc.factory.create("GLFW Window"))
    {
        if (!glfwInit())
        {
            throw Acorn::Core::DetailedError("GLFW", "Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(
            desc.width,
            desc.height,
            desc.title.c_str(),
            nullptr, nullptr);
        
        if (!m_window)
        {
            glfwTerminate();
            ACORN_ASSERT(false && "Failed to create GLFW window");
        }

        makeContextCurrent();
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
    
    void Window::makeContextCurrent()
    {
        glfwMakeContextCurrent(m_window);
    }

    void Window::releaseCurrentContext()
    {
        glfwMakeContextCurrent(nullptr);
    }
}
