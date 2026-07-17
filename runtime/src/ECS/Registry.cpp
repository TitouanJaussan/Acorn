#include "Acorn/ECS/Registry.hpp"

namespace Acorn::ECS
{
    Registry::Registry(ECSManager& lock)
        : m_entityManager(),
          m_componentArrays()
    {
        (void)lock;
    }

    void Registry::destroyEntity(EntityID id)
    {
        m_entityManager.destroy(id);
    }
}
