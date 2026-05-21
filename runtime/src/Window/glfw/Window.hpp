#ifndef ACORN_GLFW_WINDOW_HPP
#define ACORN_GLFW_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Acorn/Window/Window.hpp"
#include "Window/glfw/WindowDescriptor.hpp"

namespace Acorn::Window::GLFW
{
    class Window final : public BaseWindow
    {
    public:
        Window(WindowDescriptor descriptor);
        ~Window();

        void pollEvents() override;
        bool shouldClose() override;
        void swapBuffers() override;

    private:
        GLFWwindow* m_window{nullptr};

        Core::Logger m_logger;
    };
}

#endif /* ACORN_GLFW_WINDOW_HPP */
