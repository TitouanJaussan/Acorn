#ifndef ACORN_MODULE_REGISTRY_HPP
#define ACORN_MODULE_REGISTRY_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/UniquePtr.hpp"
#include "Acorn/Module/RuntimeModule.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleRegistry
    {
    public:
        ModuleRegistry(Core::LoggerFactory& factory);

        void registerModule(UniquePtr<RuntimeModule> mod);
        const ArrayList<UniquePtr<RuntimeModule>>& getModules() const;

    private:
        Core::Logger m_logger;
        ArrayList<UniquePtr<RuntimeModule>> m_modules;
    };
}

#endif /* ACORN_MODULE_REGISTRY_HPP */
