#ifndef MODULE_MANIFEST_HPP
#define MODULE_MANIFEST_HPP

#include "Acorn/Base/Version/Version.hpp"
#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModuleManifest
    {
        String name;
        Version::Version runtimeVersion;
        ArrayList<String> dependencies;
    };
}

#endif /* MODULE_MANIFEST_HPP */
