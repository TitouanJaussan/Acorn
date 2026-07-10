#ifndef ACORN_MODULE_LOADING_CTX
#define ACORN_MODULE_LOADING_CTX

#include "Acorn/EngineAPI.hpp"

#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Filesystem/Filesystem.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModLoadingCtx
    {
        ModuleRegistry& modRegistry;
        Filesystem::Filesystem& filesystem;
        Runtime::API runtimeAPI;
    };
}

#endif /* ACORN_MODULE_LOADING_CTX */
