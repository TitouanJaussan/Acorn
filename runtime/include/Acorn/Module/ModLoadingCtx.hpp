#ifndef ACORN_MODULE_LOADING_CTX
#define ACORN_MODULE_LOADING_CTX

#include "Acorn/EngineAPI.hpp"

#include "Acorn/Core/Runtime/RuntimeAPI.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModLoadingCtx
    {
        ModuleRegistry& modRegistry;
        Core::RuntimeAPI runtimeAPI;
    };
}

#endif /* ACORN_MODULE_LOADING_CTX */
