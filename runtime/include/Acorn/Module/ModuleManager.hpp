#ifndef ACORN_MODULE_MANAGER_HPP
#define ACORN_MODULE_MANAGER_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Core/Runtime/RuntimeAPI.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleManager
    {
    public:
        ModuleManager(Core::LoggerFactory& factory);

        void loadModules(std::filesystem::path modsFolder,
            Core::LoggerFactory& factory, Core::RuntimeAPI api);

        ArrayList<String> getModNames() const;

        void callInit();
        void callUpdate();
        void callUnload();

    private:
        void call(std::function<void(RuntimeModule&)> fn);

        Core::Logger m_logger;

        ModuleLoader m_modLoader;
        ModuleRegistry m_modRegistry;
    };
}

#endif /* ACORN_MODULE_MANAGER_HPP */
