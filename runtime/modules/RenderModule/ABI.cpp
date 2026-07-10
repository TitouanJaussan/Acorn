#include <Acorn/Module/ModuleError.hpp>

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

    auto* windowModAPI = mod->m_runtimeAPI.getModuleAPIHandle("Window");

    if (!windowModAPI)
        throw Acorn::Module::ModuleError(
            "Couldn't access window module API"
        );

    mod->m_runtimeAPI.getThreadingManager().m_serviceManager.addService(
        Acorn::UniquePtr<Acorn::Threading::Service>(
            mem_new<RenderService>(
                mod->m_runtimeAPI.getLoggerFactory(),
                mod->m_runtimeAPI.getThreadingManager(),
                *windowModAPI
            )
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
