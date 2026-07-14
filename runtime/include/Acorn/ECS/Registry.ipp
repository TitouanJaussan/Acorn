#pragma once

#include "Acorn/ECS/Registry.hpp"
#include "Acorn/ECS/ComponentArray.hpp"

namespace Acorn::ECS
{
    EntityID Registry::newEntity(auto&&... components)
    {
        EntityID entity = m_entityManager.create();

        ([&]
        {
            addComponent(entity, components);
        } (), ...);

        return entity;
    }

    template<typename T>
    void Registry::addComponent(EntityID id, T component)
    {
        const auto [it, inserted] = m_componentArrays.try_emplace(
            typeid(T),
            UniquePtr<ComponentArray<T>>::create()
        );

        auto& arr = *static_cast<ComponentArray<T>*>(it->second.getPtr());
        arr.add(id, std::move(component));
    }

    template<typename T>
    T* Registry::getComponent(EntityID id)
    {
        const auto it = m_componentArrays.find(typeid(T));

        if (it == m_componentArrays.end())
            return nullptr;

        return static_cast<ComponentArray<T>*>(it->second.getPtr())->get(id);
    }

    template<typename T>
    void Registry::removeComponent(EntityID id)
    {
        const auto it = m_componentArrays.find(typeid(T));

        if (it == m_componentArrays.end())
            return;

        static_cast<ComponentArray<T>*>(it->second.getPtr())->remove(id);
    }

    template<typename T>
    void Registry::foreach(std::function<void(EntityID, T&)> fn)
    {
        const auto it = m_componentArrays.find(typeid(T));

        if (it == m_componentArrays.end())
            return;

        const ComponentArray<T>& array =
            *static_cast<ComponentArray<T>*>(it->second.getPtr());

        size_t i{0};
        for (T& comp: array.getDense())
            fn(array.getDenseToEntity()[i++], comp);
    }
}
