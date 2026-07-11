#include "Acorn/Module/ModuleManager.hpp"
#include "Acorn/Module/ModLoadingCtx.hpp"
#include "Acorn/Core/Runtime/Engine.hpp"
#include "Acorn/Base/Assert.hpp"

namespace Acorn::Module
{
    ModuleManager::ModuleManager(Base::LoggerFactory& factory)
        : m_logger(factory.create("ModuleManager")),
          m_modLoader(factory),
          m_modRegistry(factory)
    {}

    ModuleManagerHandle ModuleManager::newHandle() noexcept
    {
        return ModuleManagerHandle(*this);
    }

    void ModuleManager::loadModules(std::filesystem::path   modsFolder,
                                    Filesystem::Filesystem& filesystem,
                                    Runtime::API            api)
    {
        m_modLoader.loadModules(
            std::move(modsFolder),
            ModLoadingCtx
            {
                .modRegistry = m_modRegistry,
                .filesystem = filesystem,
                .runtimeAPI = std::move(api)
            }
        );
    }
    
    void ModuleManager::callInit(Runtime::Engine& engine)
    {
        call([&engine, this](RuntimeModule& mod)
        {
            mod.init(engine.createAPI(), engine.getLoggerFactory());

            ACORN_ASSERT(mod.getAPI());
            m_modRegistry.updateModuleAPI(mod.getManifest().name, mod.getAPI());
        }, "init");
    }
    
    void ModuleManager::callUpdate()
    {
        call([](RuntimeModule& mod)
        {
            mod.update();
        }, "update");
    }

    void ModuleManager::callUnload()
    {
        call([](RuntimeModule& mod)
        {
            mod.unload();
        }, "unload");
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

    RuntimeModule* ModuleManager::getModule(String modName) const
    {
        return m_modRegistry.getModule(std::move(modName));
    }

    APIHandle* ModuleManager::getModuleAPIHandle(String modName) const
    {
        return m_modRegistry.getAPIHandle(std::move(modName));
    }

    void ModuleManager::call(std::function<void(RuntimeModule&)> fn,
        const char* fnName)
    {
        const auto& mods = m_modRegistry.getModules();

        for (size_t i = 0; i < mods.getSize(); ++i)
        {
            try
            {
                fn(*mods[i]);
            }
            catch (const Base::DetailedError& err)
            {
                m_logger.error(
                    "An error occured in {}Module::{} : {}",
                    mods[i]->getManifest().name,
                    fnName,
                    err.what()
                );
            }
        }
    }
}
