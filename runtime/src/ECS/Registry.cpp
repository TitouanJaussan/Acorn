#include <utility>

#include "Acorn/ECS/Registry.hpp"

namespace Acorn::ECS
{
    Registry::Registry()
        : m_entityManager(),
          m_componentArrays()
    {}

    void Registry::destroyEntity(EntityID id)
    {
        m_entityManager.destroy(id);
    }
}
