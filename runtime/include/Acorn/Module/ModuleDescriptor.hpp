#ifndef ACORN_MODULE_DESCRIPTOR_HPP
#define ACORN_MODULE_DESCRIPTOR_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModuleDescriptor
    {
        std::filesystem::path libPath;
    };
}

#endif /* ACORN_MODULE_DESCRIPTOR_HPP */
