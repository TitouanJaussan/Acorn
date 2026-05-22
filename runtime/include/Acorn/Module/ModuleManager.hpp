#ifndef ACORN_MODULE_MANAGER_HPP
#define ACORN_MODULE_MANAGER_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Logging/LoggerFactory.hpp"
#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"

#include <filesystem>

namespace Acorn::Module
{
    class ENGINE_API ModuleManager
    {
    public:
        ModuleManager(Core::LoggerFactory& factory);

        void loadModules(std::filesystem::path modsFolder);

        void callLoad(Core::LoggerFactory& factory);
        void callUpdate();
        void callUnload();

    private:
        void call(std::function<void(Module&)> fn);

        ModuleLoader m_modLoader;
        ModuleRegistry m_modRegistry;
    };
}

#endif /* ACORN_MODULE_MANAGER_HPP */
