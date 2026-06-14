#ifndef MODULE_MANIFEST_HPP
#define MODULE_MANIFEST_HPP

#include "Acorn/Core/Version/Version.hpp"
#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModuleManifest
    {
        const String name;
        const Version::Version runtimeVersion;
        const ArrayList<String> dependencies;
    };
}

#endif /* MODULE_MANIFEST_HPP */
