#include <Acorn/Core/Memory/Mem.hpp>

#include "RenderModule.hpp"

static const Acorn::Module::ModuleManifest MANIFEST = 
{
    .name = "Render",
    .runtimeVersion = Acorn::Version::Version{0, 1, 1},

    .dependencies = nullptr,
    .dependenciesCount = 0
};

RenderModule::RenderModule(Acorn::Core::RuntimeAPI api, Acorn::Core::Logger logger)
    : Acorn::Module::Module(api, logger)
{}

void RenderModule::init()
{
    m_logger.info("Created Render Module!");
}

void RenderModule::update()
{

}

void RenderModule::unload()
{

}

Acorn::Module::Module* createModule(
        Acorn::Core::RuntimeAPI api,
        Acorn::Core::Logger logger)
{
    return mem_new<RenderModule>(api, logger);
}

void destroyModule(Acorn::Module::Module* mod)
{
    mem_delete(mod);
}

const Acorn::Module::ModuleManifest* getManifest()
{
    return &MANIFEST;
}
