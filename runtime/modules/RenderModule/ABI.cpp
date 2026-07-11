#include <Acorn/Module/ModuleError.hpp>
#include <Acorn/Core/Runtime/Systems.hpp>

#include "ABI.hpp"
#include "RenderService.hpp"

static const Acorn::Module::ModuleManifest MANIFEST =
{
    .name = "Render",
    .runtimeVersion = Acorn::Version::Version{0, 2, 2},
    .dependencies = { "Window" }
};

static RenderModule*    mod{nullptr};
static RenderModuleAPI* modAPI{nullptr};

void init(
    Acorn::Runtime::API api,
    Acorn::Base::Logger logger)
{
    mod    = mem_new<RenderModule>(std::move(api), std::move(logger));
    modAPI = mem_new<RenderModuleAPI>(mod);

    auto* windowModAPI = mod->runtimeAPI.module().getModuleAPIHandle("Window");

    if (!windowModAPI)
        throw Acorn::Module::ModuleError(
            "Couldn't access window module API"
        );

    mod->runtimeAPI
        .threading()
        .spawnService(
            Acorn::UniquePtr<RenderService>::create(
                mod->runtimeAPI.getLoggerFactory(),
                *windowModAPI
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
    mod = nullptr;
}

RenderModuleAPI* getAPI()
{
    return modAPI;
}

const Acorn::Module::ModuleManifest* getManifest()
{
    return &MANIFEST;
}
