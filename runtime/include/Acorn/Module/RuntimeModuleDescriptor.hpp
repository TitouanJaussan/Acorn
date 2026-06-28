#ifndef ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP
#define ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/DynamicLib/DynamicLibrary.hpp"

namespace Acorn::Module
{
    class Runtime;

    struct ENGINE_API RuntimeModuleDescriptor
    {
        Lib::DynamicLibrary lib;
    };
}

#endif /* ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP */
