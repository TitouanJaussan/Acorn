#ifndef WINDOW_MODULE_ABI_HPP
#define WINDOW_MODULE_ABI_HPP

#include <Acorn/Module/ModuleManifest.hpp>
#include <Acorn/Core/Runtime/RuntimeAPI.hpp>

#include "Export.hpp"
#include "API.hpp"

extern "C"
{
    WINDOW_MODULE_EXPORT void init(
        Acorn::Core::RuntimeAPI runtimeAPI,
        Acorn::Core::Logger logger);
    WINDOW_MODULE_EXPORT void update();
    WINDOW_MODULE_EXPORT void unload();

    WINDOW_MODULE_EXPORT WindowModuleAPI* getAPI();
    WINDOW_MODULE_EXPORT const Acorn::Module::ModuleManifest* getManifest();
}

#endif /* WINDOW_MODULE_ABI_HPP */
