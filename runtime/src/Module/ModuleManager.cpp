#include "Acorn/Module/ModuleManager.hpp"

namespace Acorn::Module
{
    ModuleManager::ModuleManager(Core::LoggerFactory& factory)
        : m_modLoader(factory),
          m_modRegistry(factory)
    {}

    void ModuleManager::loadModules(std::filesystem::path modsFolder)
    {
        m_modLoader.loadModules(modsFolder, m_modRegistry);
    }

    void ModuleManager::callLoad(Core::LoggerFactory& factory)
    {
        call([&factory](Module& mod)
        {
            mod.load(factory.create(mod.name));
        });
    }
    
    void ModuleManager::callUpdate()
    {
        call([](Module& mod)
        {
            mod.update();
        });
    }

    void ModuleManager::callUnload()
    {
        call([](Module& mod)
        {
            mod.unload();
        });
    }

    void ModuleManager::call(std::function<void(Module&)> fn)
    {
        for (const auto& mod: m_modRegistry.getModules())
            fn(*mod);
    }
}
