#ifndef ACORN_MODULE_MANAGER_HPP
#define ACORN_MODULE_MANAGER_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Core/Runtime/RuntimeAPI.hpp"

#include <filesystem>

namespace Acorn::Module
{
    class ENGINE_API ModuleManager
    {
    public:
        ModuleManager(Core::LoggerFactory& factory);

        void loadModules(std::filesystem::path modsFolder,
            Core::LoggerFactory& factory, Core::RuntimeAPI api);

        void callInit();
        void callUpdate();
        void callUnload();

    private:
        void call(std::function<void(RuntimeModule&)> fn);

        ModuleLoader m_modLoader;
        ModuleRegistry m_modRegistry;
    };
}

#endif /* ACORN_MODULE_MANAGER_HPP */
