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

    Threading::JobScheduler& RuntimeAPI::getJobScheduler() const noexcept
    {
        return m_runtime.getJobScheduler();
    }
}
