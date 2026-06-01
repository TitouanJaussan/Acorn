#ifndef MODULE_MANIFEST_HPP
#define MODULE_MANIFEST_HPP

#include <cstddef>

#include "Acorn/Core/Version/Version.hpp"
#include "Acorn/EngineAPI.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModuleManifest
    {
        const char*      name;
        Version::Version runtimeVersion;

        const char**     dependencies;
        const size_t     dependenciesCount;
    };
}

#endif /* MODULE_MANIFEST_HPP */
