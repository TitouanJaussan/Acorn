#ifndef ACORN_MODULE_REGISTRY_HPP
#define ACORN_MODULE_REGISTRY_HPP

#include <vector>
#include <memory>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Module/Module.hpp"
#include "Acorn/Core/Logging/Logger.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleRegistry
    {
    public:
        ModuleRegistry(Core::Logger& runtimeLogger);

        void registerMod(std::unique_ptr<Module> mod);

        const std::vector<std::unique_ptr<Module>>& getModules() const;

    private:
        Core::Logger& m_runtimeLogger;
        std::vector<std::unique_ptr<Module>> m_modules;
    };
}

#endif /* ACORN_MODULE_REGISTRY_HPP */
