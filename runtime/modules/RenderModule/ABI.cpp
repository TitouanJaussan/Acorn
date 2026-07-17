#include <Acorn/Module/ModuleError.hpp>
#include <Acorn/Core/Runtime/Systems.hpp>

#include <WindowModule/ModuleName.hpp>
#include <RenderModule/ModuleName.hpp>

#include "ABI.hpp"
#include "RenderService.hpp"

static RenderModule*    mod{nullptr};
static RenderModuleAPI* modAPI{nullptr};

void init(
    Acorn::Runtime::API api,
    Acorn::Base::Logger logger)
{
    mod    = mem_new<RenderModule>(std::move(api), std::move(logger));
    modAPI = mem_new<RenderModuleAPI>(mod);

    auto windowModAPI = mod->runtimeAPI
        .module()
        .getModuleAPIHandle(WINDOW_MODULE_NAME);

    auto renderModAPI = mod->runtimeAPI
        .module()
        .getModuleAPIHandle(RENDER_MODULE_NAME);

    mod->runtimeAPI.threading()
        .spawnService(
            Acorn::UniquePtr<RenderService>::create(
                mod->runtimeAPI.getLoggerFactory(),
                windowModAPI,
                renderModAPI
            )
        );
}

void update()
{

}

void unload()
{
    mem_delete(modAPI);
    mem_delete(mod);

    modAPI = nullptr;
    mod = nullptr;
}

RenderModuleAPI* getAPI()
{
    return modAPI;
}
