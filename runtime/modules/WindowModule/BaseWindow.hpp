#ifndef ACORN_BASE_WINDOW_HPP
#define ACORN_BASE_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "API.hpp"

class API BaseWindow
{
public:
    BaseWindow() {};
    virtual ~BaseWindow() {};

    virtual void pollEvents() = 0;
    virtual bool shouldClose() = 0;
    virtual void swapBuffers() = 0;
};

#endif /* ACORN_BASE_WINDOW_HPP */
