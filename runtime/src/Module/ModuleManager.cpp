#include "Acorn/Module/ModuleManager.hpp"

namespace Acorn::Module
{
    ModuleManager::ModuleManager(Core::LoggerFactory& factory)
        : m_modLoader(factory),
          m_modRegistry(factory)
    {}

    void ModuleManager::loadModules(std::filesystem::path modsFolder,
        Core::LoggerFactory& factory, Core::RuntimeAPI api)
    {
        m_modLoader.loadModules(
            modsFolder,
            m_modRegistry,
            factory,
            api
        );
    }

    void ModuleManager::callInit()
    {
        call([](RuntimeModule& mod)
        {
            mod.init();
        });
    }
    
    void ModuleManager::callUpdate()
    {
        call([](RuntimeModule& mod)
        {
            mod.update();
        });
    }

    void ModuleManager::callUnload()
    {
        call([](RuntimeModule& mod)
        {
            mod.unload();
        });
    }

    void ModuleManager::call(std::function<void(RuntimeModule&)> fn)
    {
        for (const auto& mod: m_modRegistry.getModules())
            fn(*mod);
    }
}
