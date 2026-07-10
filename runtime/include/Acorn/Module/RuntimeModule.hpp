#ifndef ACORN_RUNTIME_MODULE_HPP
#define ACORN_RUNTIME_MODULE_HPP

#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Module/ModuleManifest.hpp"
#include "Acorn/Module/RuntimeModuleDescriptor.hpp"

namespace Acorn::Module
{
    class Module;

    using InitFn   = void(*)(Runtime::API api, Base::Logger logger);
    using UpdateFn = void(*)();
    using UnloadFn = void(*)();

    struct ENGINE_API ModuleWrapper
    {
        InitFn   m_init;
        UpdateFn m_update;
        UnloadFn m_unload;
        void*    m_api;
    };

    class ENGINE_API RuntimeModule final
    {
    public:
        explicit RuntimeModule(RuntimeModuleDescriptor desc);
        ~RuntimeModule();

        void  init(
            Runtime::API api,
            Base::LoggerFactory& factory);
        void  update();
        void  unload();
        void* getAPI();

        const ModuleManifest& getManifest() const;
        std::filesystem::path getLibPath() const;

    private:
        Lib::DynamicLibrary m_lib;
        ModuleManifest m_manifest;
        ModuleWrapper m_module;
    };
}

#endif /* ACORN_RUNTIME_MODULE_HPP */
