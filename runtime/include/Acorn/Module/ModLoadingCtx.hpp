#ifndef ACORN_MOD_LOADING_CTX_HPP
#define ACORN_MOD_LOADING_CTX_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Runtime/RuntimeAPI.hpp"

namespace Acorn::Module
{
    struct ENGINE_API ModLoadingCtx
    {
        ModuleRegistry&       modRegistry;
        Core::LoggerFactory&  loggerFactory;
        Core::RuntimeAPI      runtimeAPI;
    };
}

#endif /* ACORN_MOD_LOADING_CTX_HPP */
