#include "Acorn/Module/ModuleRegistry.hpp"

namespace Acorn::Module
{
    ModuleRegistry::ModuleRegistry(Core::LoggerFactory& factory)
        : m_modules{},
          m_logger(factory.create("ModRegistry"))
    {}

    void ModuleRegistry::registerModule(std::unique_ptr<RuntimeModule> mod)
    {
        const auto& ref = m_modules.emplace_back(std::move(mod));
    }

    const std::vector<std::unique_ptr<RuntimeModule>>& ModuleRegistry::getModules() const
    {
        return m_modules;
    }
}
