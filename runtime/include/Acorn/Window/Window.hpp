#ifndef ACORN_WINDOW_HPP
#define ACORN_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Window
{
    class ENGINE_API BaseWindow
    {
    public:
        BaseWindow() {};
        virtual ~BaseWindow() {};

        virtual void pollEvents() = 0;
        virtual bool shouldClose() = 0;
        virtual void swapBuffers() = 0;

    private:
        GLFWwindow* m_windowPtr{nullptr};
    };
}

#endif /* ACORN_WINDOW_HPP */
