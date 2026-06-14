#include "Acorn/Module/ModuleManager.hpp"
#include "Acorn/Module/ModLoadingCtx.hpp"

namespace Acorn::Module
{
    ModuleManager::ModuleManager(Core::LoggerFactory& factory)
        : m_logger(factory.create("ModuleManager")),
          m_modLoader(factory),
          m_modRegistry(factory)
    {}

    void ModuleManager::loadModules(std::filesystem::path modsFolder,
        Core::LoggerFactory& factory, Core::RuntimeAPI api)
    {
        m_modLoader.loadModules(
            modsFolder,
            ModLoadingCtx
            {
                .modRegistry = m_modRegistry,
                .loggerFactory = factory,
                .runtimeAPI = std::move(api)
            }
        );
    }

    ArrayList<String> ModuleManager::getModNames() const
    {
        const auto& mods = m_modRegistry.getModules();

        ArrayList<String> names{};
        names.setCapacity(m_modRegistry.getModules().getSize());

        for (size_t i = 0; i < mods.getSize(); ++i)
            names.append(mods[i]->getManifest().name);

        return names;
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
        const auto& mods = m_modRegistry.getModules();

        for (size_t i = 0; i < mods.getSize(); ++i)
            fn(*mods[i]);
    }
}
