#ifndef ACORN_MODULE_MANAGER_HPP
#define ACORN_MODULE_MANAGER_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Templates/String.hpp"
#include "Acorn/Filesystem/Filesystem.hpp"
#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Module/ModuleLoader.hpp"
#include "Acorn/Module/ModuleRegistry.hpp"
#include "Acorn/Module/ModuleManagerHandle.hpp"

namespace Acorn::Module
{
    class ENGINE_API ModuleManager
    {
    public:
        ModuleManager(Base::LoggerFactory& factory);

        ModuleManagerHandle newHandle() noexcept;
        void loadModules(std::filesystem::path   modsFolder,
                         Filesystem::Filesystem& filesystem,
                         Runtime::API            runtimeAPI);

        void callInit(Runtime::API runtimeAPI, Base::LoggerFactory& factory);
        void callUpdate();
        void callUnload();

        ArrayList<String> getModNames() const;

        ModuleRegistry modRegistry;

    private:
        void call(std::function<void(RuntimeModule&)> fn, const char* fnName);

        Base::Logger m_logger;

        ModuleLoader   m_modLoader;
    };
}

#endif /* ACORN_MODULE_MANAGER_HPP */
