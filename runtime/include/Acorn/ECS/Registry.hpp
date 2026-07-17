#ifndef ACORN_ECS_REGISTRY_HPP
#define ACORN_ECS_REGISTRY_HPP

#include <typeindex>
#include <unordered_map>
#include <functional>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/ECS/EntityManager.hpp"
#include "Acorn/ECS/IComponentArray.hpp"
#include "Acorn/Templates/UniquePtr.hpp"

namespace Acorn::ECS
{
    class ECSManager;

    class ENGINE_API Registry
    {
    public:
        explicit Registry(ECSManager& lock);

        Registry(const Registry&) = delete;
        Registry& operator=(const Registry&) = delete;

        EntityID newEntity(auto&&... components);
        void destroyEntity(EntityID id);
        
        // Maybe rename to setComponent or idk so that
        // the name relfects what happens when the component already exists
        template<typename T>
        void addComponent(EntityID id, T component);

        template<typename T>
        T* getComponent(EntityID id);

        template<typename T>
        void removeComponent(EntityID id);

        template<typename T>
        void foreach(std::function<void(EntityID, T&)> fn);

    private:
        EntityManager m_entityManager;
        std::unordered_map<std::type_index,
            UniquePtr<IComponentArray>> m_componentArrays;
    };
}

#include "Acorn/ECS/Registry.ipp"

#endif /* ACORN_ECS_REGISTRY_HPP */
