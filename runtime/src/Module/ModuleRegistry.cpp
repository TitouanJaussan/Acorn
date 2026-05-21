#include "Acorn/Module/ModuleRegistry.hpp"

namespace Acorn::Module
{
    ModuleRegistry::ModuleRegistry(Core::Logger& runtimeLogger)
        : m_modules{},
          m_runtimeLogger(runtimeLogger)
    {}

    void ModuleRegistry::registerMod(std::unique_ptr<Module> mod)
    {
        const auto& ref = m_modules.emplace_back(std::move(mod));
        
        m_runtimeLogger.info(
            "Loaded module '{}' ('{}')",
            ref->name,
            ref->libPath().filename().string()
        );
    }

    const std::vector<std::unique_ptr<Module>>& ModuleRegistry::getModules() const
    {
        return m_modules;
    }
}
