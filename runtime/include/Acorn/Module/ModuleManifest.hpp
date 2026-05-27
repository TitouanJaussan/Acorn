#ifndef MODULE_MANIFEST_HPP
#define MODULE_MANIFEST_HPP

#include <cstddef>

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModuleManifest
    {
        const char* name;
        const char** dependencies;
        const size_t dependenciesCount;
    };
}

#endif /* MODULE_MANIFEST_HPP */
