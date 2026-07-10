#ifndef WINDOW_MODULE_ABI_HPP
#define WINDOW_MODULE_ABI_HPP

#include <Acorn/Module/ModuleManifest.hpp>
#include <Acorn/Core/Runtime/API.hpp>

#include "Export.hpp"
#include "API.hpp"

extern "C"
{
    WINDOW_MODULE_EXPORT void init(
        Acorn::Runtime::API runtimeAPI,
        Acorn::Base::Logger logger);
    WINDOW_MODULE_EXPORT void update();
    WINDOW_MODULE_EXPORT void unload();

    WINDOW_MODULE_EXPORT WindowModuleAPI* getAPI();
    WINDOW_MODULE_EXPORT const Acorn::Module::ModuleManifest* getManifest();
}

#endif /* WINDOW_MODULE_ABI_HPP */
