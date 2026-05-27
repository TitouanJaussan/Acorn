#ifndef ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP
#define ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP

#include "Acorn/Core/Runtime/RuntimeAPI.hpp"
#include "Acorn/EngineAPI.hpp"
#include "Acorn/DynamicLib/DynamicLibrary.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"

namespace Acorn::Module
{
    class Runtime;

    struct ENGINE_API RuntimeModuleDescriptor
    {
        Lib::DynamicLibrary lib;
        Core::RuntimeAPI api;
        Core::LoggerFactory loggerFactory;
    };
}

#endif /* ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP */
