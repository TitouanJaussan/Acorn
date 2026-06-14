#ifndef ACORN_RUNTIME_MODULE_HPP
#define ACORN_RUNTIME_MODULE_HPP

#include "Acorn/EngineAPI.hpp"

#include "Acorn/Module/ModuleManifest.hpp"
#include "Acorn/Module/RuntimeModuleDescriptor.hpp"

namespace Acorn::Module
{
    struct Module;

    using DestroyModFn     = void(*)(Module*);
    using GetModManifestFn = ModuleManifest*(*)(void);

    struct ENGINE_API ModuleWrapper
    {
        ModuleWrapper(Module* module, DestroyModFn dtor) noexcept;
        ~ModuleWrapper();

        Module* m_mod;
        const DestroyModFn m_dtor;
    };

    class ENGINE_API RuntimeModule final
    {
    public:
        explicit RuntimeModule(RuntimeModuleDescriptor desc);
        ~RuntimeModule();

        void init();
        void update();
        void unload();

        const ModuleManifest& getManifest() const;
        std::filesystem::path getLibPath() const;

    private:
        Lib::DynamicLibrary m_lib;
        ModuleManifest m_manifest;
        ModuleWrapper m_module;
    };
}

#endif /* ACORN_RUNTIME_MODULE_HPP */
