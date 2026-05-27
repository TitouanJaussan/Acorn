#ifndef ACORN_GLFW_WINDOW_DESCRIPTOR_HPP
#define ACORN_GLFW_WINDOW_DESCRIPTOR_HPP

#include <string>

#include "Acorn/Core/Logging/Logger.hpp"

namespace GLFW
{
    struct WindowDescriptor
    {
        Acorn::Core::Logger& moduleLogger;
        const std::string title{"<Unnamed>"};
        const int width{1200};
        const int height{800};
    };
}

#endif /* ACORN_GLFW_WINDOW_DESCRIPTOR_HPP */
