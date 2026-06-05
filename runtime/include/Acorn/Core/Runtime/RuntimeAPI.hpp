#ifndef ACORN_RUNTIME_API_HPP
#define ACORN_RUNTIME_API_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Version/Version.hpp"
#include "Acorn/Threading/ThreadingManager.hpp"

namespace Acorn::Core
{
    class Runtime;

    class ENGINE_API RuntimeAPI
    {
    public:
        RuntimeAPI(Runtime& runtime, Version::Version runtimeVersion);

        void stopRuntime() const;
        Version::Version version() const noexcept;

        Core::LoggerFactory& getLoggerFactory() const noexcept;
        Threading::ThreadingManager& getThreadingManager() const noexcept;

    private:
        Runtime& m_runtime;
        Version::Version m_version;
    };
}

#endif /* ACORN_RUNTIME_API_HPP */
