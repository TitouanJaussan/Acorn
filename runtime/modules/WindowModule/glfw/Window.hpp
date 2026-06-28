#ifndef ACORN_GLFW_WINDOW_HPP
#define ACORN_GLFW_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "BaseWindow.hpp"
#include "glfw/WindowDescriptor.hpp"
#include "Acorn/Core/Logging/Logger.hpp"

namespace GLFW
{
    class Window final : public BaseWindow
    {
    public:
        Window(WindowDescriptor descriptor);
        ~Window();

        void pollEvents() override;
        bool shouldClose() override;
        void swapBuffers() override;
        void makeContextCurrent() override;
        void releaseCurrentContext() override;

    private:
        GLFWwindow* m_window{nullptr};

        Acorn::Core::Logger m_logger;
    };
}

#endif /* ACORN_GLFW_WINDOW_HPP */
