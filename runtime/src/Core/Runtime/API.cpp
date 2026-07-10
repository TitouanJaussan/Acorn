#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Core/Runtime/Engine.hpp"

namespace Acorn::Runtime
{
    API::API(Engine& engine, Version::Version engineVersion)
        : m_engine(engine),
          m_version(engineVersion)
    {}

    void API::stopEngine() const
    {
        m_engine.stop();
    }
    
    Version::Version API::version() const noexcept
    {
        return m_version;
    }

    Base::LoggerFactory& API::getLoggerFactory() const noexcept
    {
        return m_engine.getLoggerFactory();
    }

    Threading::ThreadingManager& API::getThreadingManager() const noexcept
    {
        return m_engine.m_systems.threadingManager;
    }

    Module::APIHandle* API::getModuleAPIHandle(String modName) const
    {
        return m_engine.m_systems.modManager
            .getModuleAPIHandle(std::move(modName));
    }
}
