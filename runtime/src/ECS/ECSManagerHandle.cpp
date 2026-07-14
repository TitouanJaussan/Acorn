#include "Acorn/ECS/ECSManagerHandle.hpp"
#include "Acorn/ECS/Registry.hpp"
#include "Acorn/ECS/ECSManager.hpp"

namespace Acorn::ECS
{
    ECSManagerHandle::ECSManagerHandle(ECSManager& handle)
        : m_handle(handle)
    {}

    Registry ECSManagerHandle::createRegistry()
    {
        return m_handle.createRegistry();
    }
}
