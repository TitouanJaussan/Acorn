#ifndef ACORN_BASE_WINDOW_HPP
#define ACORN_BASE_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Export.hpp"

class WINDOW_MODULE_EXPORT BaseWindow
{
public:
    BaseWindow() {};
    virtual ~BaseWindow() {};

    virtual void pollEvents() = 0;
    virtual bool shouldClose() = 0;
    virtual void swapBuffers() = 0;
    virtual void makeContextCurrent() = 0;
    virtual void releaseCurrentContext() = 0;
};

#endif /* ACORN_BASE_WINDOW_HPP */
