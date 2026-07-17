#include "Acorn/Core/Runtime/API.hpp"
#include "Acorn/Core/Runtime/Engine.hpp"
#include "Acorn/Core/Runtime/Systems.hpp"

namespace Acorn::Runtime
{
    API::API(Engine& engine)
        : m_engine(engine)
    {}

    void API::stopEngine() const
    {
        m_engine.stop();
    }
    
    Version::Version API::getVersion() const noexcept
    {
        return m_engine.version();
    }

    Base::LoggerFactory& API::getLoggerFactory() const noexcept
    {
        return m_engine.getLoggerFactory();
    }

    Threading::ThreadingManagerHandle API::threading()
    {
        return m_engine.systems.threadingManager.newHandle();
    }

    Filesystem::FilesystemHandle API::filesystem()
    {
        return m_engine.systems.filesystem.newHandle();
    }

    Module::ModuleManagerHandle API::module()
    {
        return m_engine.systems.modManager.newHandle();
    }

    ECS::ECSManagerHandle API::ecs()
    {
        return m_engine.systems.ecsManager.newHandle();
    }
}
