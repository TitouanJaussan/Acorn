#include <glad/include/glad/glad.h>

#include <Acorn/Core/Memory/Mem.hpp>
#include <Acorn/Templates/UniquePtr.hpp>
#include <Acorn/Threading/ServiceDescriptor.hpp>

#include "RenderModule.hpp"

using namespace std::chrono_literals;

static const Acorn::Module::ModuleManifest MANIFEST = 
{
    .name = "Render",
    .runtimeVersion = Acorn::Version::Version{0, 2, 1},

    .dependencies = { "Window" }
};

RenderService::RenderService(Acorn::Core::LoggerFactory& factory,
    Acorn::Threading::ThreadingManager& threadingManager)
    : Acorn::Threading::Service(Acorn::Threading::ServiceDescriptor
        {
            .name = "Render",
            .factory = factory,
            .threadingManager = threadingManager
        })
{}

void RenderService::work()
{
    while (m_running)
    {
        m_logger.warn("Hello, from service!");
        std::this_thread::sleep_for(.5s);
    }
}

RenderModule::RenderModule(Acorn::Core::RuntimeAPI api, Acorn::Core::Logger logger)
    : Acorn::Module::Module(std::move(api), std::move(logger))
{
    // m_api.getThreadingManager().m_serviceManager.addService(
    //     Acorn::UniquePtr<Acorn::Threading::Service>(
    //         mem_new<RenderService>(
    //             m_api.getLoggerFactory(),
    //             m_api.getThreadingManager()
    //         )
    //     )
    // );
}

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
