#ifndef ACORN_COMMAND_LINE_ARGUMENTS_DESCRIPTOR_HPP
#define ACORN_COMMAND_LINE_ARGUMENTS_DESCRIPTOR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"

namespace Acorn::Core
{
    struct ENGINE_API CommandLineArgumentsDescriptor
    {
        Base::LoggerFactory& factory;
        int argc;
        char** argv;
    };
}

#endif /* ACORN_COMMAND_LINE_ARGUMENTS_DESCRIPTOR_HPP */
