#ifndef ACORN_MODULE_REGISTRY_HPP
#define ACORN_MODULE_REGISTRY_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Templates/Pair.hpp"
#include "Acorn/Module/RuntimeModule.hpp"
#include "Acorn/Module/APIHandle.hpp"
#include "Acorn/Module/ModuleAPI.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleRegistry
    {
    public:
        ModuleRegistry(Base::LoggerFactory& factory);

        void registerModule(UniquePtr<RuntimeModule> mod);
        const ArrayList<UniquePtr<RuntimeModule>>& getModules() const;

        RuntimeModule* getModule(String name) const;
        APIHandle<> getAPIHandle(String modName) const;

        void updateModuleAPI(String modName, void* newApiPtr);

    private:
        Pair<bool, size_t> findModuleIndex(String modName) const;

    private:
        Base::Logger m_logger;
        ArrayList<UniquePtr<RuntimeModule>> m_modules;
        ArrayList<UniquePtr<ModuleAPI>> m_modsAPIs;
    };
}

#endif /* ACORN_MODULE_REGISTRY_HPP */
