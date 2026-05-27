#include "Acorn/Core/Runtime/RuntimeAPI.hpp"
#include "Acorn/Core/Runtime/Runtime.hpp"

namespace Acorn::Core
{
    RuntimeAPI::RuntimeAPI(Runtime& runtime)
        : m_runtime(runtime)
    {}

    void RuntimeAPI::stopRuntime() const
    {
        m_runtime.stop();
    }
}
