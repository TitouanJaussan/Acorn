#include "Acorn/Core/Runtime/RuntimeAPI.hpp"
#include "Acorn/Core/Runtime/Runtime.hpp"

namespace Acorn::Core
{
    RuntimeAPI::RuntimeAPI(Runtime& runtime, Version::Version runtimeVersion)
        : m_runtime(runtime),
          m_version(runtimeVersion)
    {}

    void RuntimeAPI::stopRuntime() const
    {
        m_runtime.stop();
    }
    
    Version::Version RuntimeAPI::version() const noexcept
    {
        return m_version;
    }

    Core::LoggerFactory& RuntimeAPI::getLoggerFactory() const noexcept
    {
        return m_runtime.getLoggerFactory();
    }

    Threading::ThreadingManager& RuntimeAPI::getThreadingManager() const noexcept
    {
        return m_runtime.getThreadingManager();
    }
}
