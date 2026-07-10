#include "Acorn/Module/RuntimeModule.hpp"

namespace Acorn::Module
{
    using GetModManifestFn = ModuleManifest*(*)(void);

    RuntimeModule::RuntimeModule(RuntimeModuleDescriptor desc)
        : m_lib(std::move(desc.lib)),
          m_manifest(std::move(desc.manifest)),
          m_module{
              .m_init   = m_lib.resolveSymbol<InitFn>("init"),
              .m_update = m_lib.resolveSymbol<UpdateFn>("update"),
              .m_unload = m_lib.resolveSymbol<UnloadFn>("unload"),
              .m_api    = nullptr
          }
    {}

    RuntimeModule::~RuntimeModule()
    {}

    void RuntimeModule::init(
        Runtime::API api,
        Base::LoggerFactory& factory)
    {
        m_module.m_init(
            std::move(api),
            factory.create((m_manifest.name + " Module").getData()));
        m_module.m_api = m_lib.resolveSymbol<void*(*)()>("getAPI")();
    }

    void RuntimeModule::update()
    {
        m_module.m_update();
    }

    void RuntimeModule::unload()
    {
        m_module.m_unload();
    }

    void* RuntimeModule::getAPI()
    {
        return m_module.m_api;
    }

    const ModuleManifest& RuntimeModule::getManifest() const
    {
        return m_manifest;
    }

    std::filesystem::path RuntimeModule::getLibPath() const
    {
        return m_lib.path;
    }
}
