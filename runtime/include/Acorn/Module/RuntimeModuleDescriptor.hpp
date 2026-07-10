#ifndef ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP
#define ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/DynamicLib/DynamicLibrary.hpp"
#include "Acorn/Module/ModuleManifest.hpp"

namespace Acorn::Module
{
    struct ENGINE_API RuntimeModuleDescriptor
    {
        Lib::DynamicLibrary lib;
        ModuleManifest manifest;
    };
}

#endif /* ACORN_RUNTIME_MODULE_DESCRIPTOR_HPP */
