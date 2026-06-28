#ifndef RENDER_MODULE_HPP
#define RENDER_MODULE_HPP

#include <Acorn/Core/Runtime/RuntimeAPI.hpp>
#include <Acorn/Core/Logging/Logger.hpp>
#include <Acorn/Module/ModuleManifest.hpp>

#include "Export.hpp"

struct RENDER_MODULE_LOCAL RenderModule
{
    Acorn::Core::RuntimeAPI m_runtimeAPI;
    Acorn::Core::Logger m_logger;
};

class RENDER_MODULE_LOCAL RenderModuleAPI
{
public:
    RenderModuleAPI(RenderModule* mod);

private:
    RenderModule* m_mod;
};

extern "C"
{
    RENDER_MODULE_EXPORT void init(
        Acorn::Core::RuntimeAPI api,
        Acorn::Core::Logger logger);
    RENDER_MODULE_EXPORT void update();
    RENDER_MODULE_EXPORT void unload();

    RENDER_MODULE_EXPORT RenderModuleAPI* getAPI();
    RENDER_MODULE_EXPORT const Acorn::Module::ModuleManifest* getManifest();
}

#endif /* RENDER_MODULE_HPP */
