#ifndef ACORN_MODULE_REGISTRY_HPP
#define ACORN_MODULE_REGISTRY_HPP

#include <vector>
#include <memory>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Module/RuntimeModule.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleRegistry
    {
    public:
        ModuleRegistry(Core::LoggerFactory& factory);

        void registerModule(std::unique_ptr<RuntimeModule> mod);

        const std::vector<std::unique_ptr<RuntimeModule>>& getModules() const;

    private:
        Core::Logger m_logger;
        std::vector<std::unique_ptr<RuntimeModule>> m_modules;
    };
}

#endif /* ACORN_MODULE_REGISTRY_HPP */
