#include "Acorn/ECS/EntityManager.hpp"

namespace Acorn::ECS
{
    EntityManager::EntityManager()
        : m_generations(),
          m_freeIndices()
    {}

    EntityID EntityManager::create()
    {
        uint32_t index{};

        if (!m_freeIndices.isEmpty())
        {
            index = m_freeIndices[m_freeIndices.getSize() - 1];
            m_freeIndices.popBack();
        }
        else
        {
            index = m_generations.getSize();
            m_generations.append(0);
        }

        return EntityID
        {
            .index = index,
            .generation = m_generations[index]
        };
    }

    void EntityManager::destroy(EntityID id)
    {
        m_generations[id.index]++;
        m_freeIndices.append(id.index);
    }

    bool EntityManager::isValid(EntityID id) const
    {
        return id.index < m_generations.getSize() &&
               m_generations[id.index] == id.generation;
    }
}
