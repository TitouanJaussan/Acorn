#ifndef ACORN_RUNTIME_API_HPP
#define ACORN_RUNTIME_API_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Version/Version.hpp"
#include "Acorn/Threading/ThreadingManager.hpp"
#include "Acorn/Module/APIHandle.hpp"

namespace Acorn::Module
{
    class RuntimeModule;
}

namespace Acorn::Runtime
{
    class Engine;

    class ENGINE_API API
    {
    public:
        API(Engine& engine, Version::Version engineVersion);

        void stopEngine() const;
        Version::Version version() const noexcept;

        Base::LoggerFactory& getLoggerFactory() const noexcept;
        Threading::ThreadingManager& getThreadingManager() const noexcept;
        Module::APIHandle* getModuleAPIHandle(String modName) const;

    private:
        Engine& m_engine;
        Version::Version m_version;
    };
}

#endif /* ACORN_RUNTIME_API_HPP */
