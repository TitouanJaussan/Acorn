#pragma once

#include "Acorn/ECS/ComponentArray.hpp"

namespace Acorn::ECS
{
    template<typename T>
    ComponentArray<T>::ComponentArray()
        : m_dense(),
          m_denseToEntity(),
          m_sparse()
    {}

    template<typename T>
    void ComponentArray<T>::add(EntityID id, T component)
    {
        if (has(id))
            return;

        m_dense.append(std::move(component));
        m_denseToEntity.append(id);
        m_sparse[id] = m_dense.getSize() - 1;
    }

    template<typename T>
    bool ComponentArray<T>::has(EntityID id)
    {
        return m_sparse.find(id) != m_sparse.end();
    }

    template<typename T>
    T* ComponentArray<T>::get(EntityID id)
    {
        const auto it = m_sparse.find(id);

        if (it == m_sparse.end())
            return nullptr;
        
        return &m_dense[it->second];
    }

    template<typename T>
    void ComponentArray<T>::remove(EntityID id)
    {
        const auto it = m_sparse.find(id);

    }

    template<typename T>
    const ArrayList<T>& ComponentArray<T>::getDense() const noexcept
    {
        return m_dense;
    }

    template<typename T>
    const ArrayList<EntityID>&
        ComponentArray<T>::getDenseToEntity() const noexcept
    {
        return m_denseToEntity;
    }
}
