#ifndef ACORN_RUNTIME_SYSTEMS_HPP
#define ACORN_RUNTIME_SYSTEMS_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Filesystem/Filesystem.hpp"
#include "Acorn/Threading/ThreadingManager.hpp"
#include "Acorn/Module/ModuleManager.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"

namespace Acorn::Runtime
{
    struct ENGINE_API Systems
    {
        Filesystem::Filesystem      filesystem;
        Threading::ThreadingManager threadingManager;
        Module::ModuleManager       modManager;

        Systems(Base::LoggerFactory& factory,
                std::filesystem::path rootDirectory);
    };
}

#endif /* ACORN_RUNTIME_SYSTEMS_HPP */
