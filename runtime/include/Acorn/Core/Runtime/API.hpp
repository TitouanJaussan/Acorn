#ifndef ACORN_RUNTIME_API_HPP
#define ACORN_RUNTIME_API_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Version/Version.hpp"
#include "Acorn/Module/ModuleManagerHandle.hpp"
#include "Acorn/Threading/ThreadingManagerHandle.hpp"
#include "Acorn/Filesystem/FilesystemHandle.hpp"
#include "Acorn/ECS/ECSManagerHandle.hpp"

namespace Acorn::Module
{
    class RuntimeModule;
}

namespace Acorn::Runtime
{
    class Engine;
    struct Systems;

    class ENGINE_API API
    {
    public:
        API(Engine& engine, Version::Version engineVersion);

        void stopEngine() const;
        Version::Version getVersion() const noexcept;
        Base::LoggerFactory& getLoggerFactory() const noexcept;

        Threading::ThreadingManagerHandle threading();
        Filesystem::FilesystemHandle      filesystem();
        Module::ModuleManagerHandle       module();
        ECS::ECSManagerHandle             ecs();

    private:
        Engine& m_engine;
        Version::Version m_version;
    };
}

#endif /* ACORN_RUNTIME_API_HPP */
