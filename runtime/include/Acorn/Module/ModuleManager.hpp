#ifndef ACORN_MODULE_MANAGER_HPP
#define ACORN_MODULE_MANAGER_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Core
{
    class Runtime;
}

namespace Acorn::Module
{
    class ENGINE_API ModuleManager
    {
    public:
        ModuleManager(Core::LoggerFactory& factory);

        void loadModules(std::filesystem::path modsFolder,
            Core::LoggerFactory& factory, Core::RuntimeAPI api);

        // TODO: If possible only pass a runtime api factory instead of the whole runtime
        void callInit(Core::Runtime& runtime);
        void callUpdate();
        void callUnload();

        ArrayList<String> getModNames() const;
        RuntimeModule*    getModule(String modName) const;
        APIHandle*        getModuleAPIHandle(String modName) const;

    private:
        void call(std::function<void(RuntimeModule&)> fn, const char* fnName);

        Core::Logger m_logger;

        ModuleLoader m_modLoader;
        ModuleRegistry m_modRegistry;
    };
}

#endif /* ACORN_MODULE_MANAGER_HPP */
