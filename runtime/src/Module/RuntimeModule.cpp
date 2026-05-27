#include "Acorn/Module/RuntimeModule.hpp"
#include "Acorn/Core/DetailedError.hpp"
#include "Acorn/Module/Module.hpp"

namespace Acorn::Module
{
    using CreateModFn = Module*(*)(Core::RuntimeAPI, Core::Logger);

    ModuleWrapper::ModuleWrapper(Module* module, DestroyModFn dtor) noexcept
        : m_mod(module),
          m_dtor(dtor)
    {}

    ModuleWrapper::~ModuleWrapper()
    {
        m_dtor(m_mod);
    }

    RuntimeModule::RuntimeModule(RuntimeModuleDescriptor desc)
        : m_lib(std::move(desc.lib)),
          m_manifest(*m_lib.resolveSymbol<GetModManifestFn>("getManifest")()),
          m_module(ModuleWrapper{
            m_lib.resolveSymbol<CreateModFn>("createModule")(
                desc.api,
                desc.loggerFactory.create(m_manifest.name)
            ),
            m_lib.resolveSymbol<DestroyModFn>("destroyModule")
          })
    {
        if (!m_module.m_mod)
            throw Core::DetailedError(
                "RuntimeModule",
                "Provided module is NULL"
            );
    }

    RuntimeModule::~RuntimeModule()
    {}

    void RuntimeModule::init()
    {
        m_module.m_mod->init();
    }

    void RuntimeModule::update()
    {
        m_module.m_mod->update();
    }

    void RuntimeModule::unload()
    {
        m_module.m_mod->unload();
    }
}
