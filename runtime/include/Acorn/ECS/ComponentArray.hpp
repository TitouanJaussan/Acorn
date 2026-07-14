#ifndef ACORN_ECS_COMPONENT_ARRAY_HPP
#define ACORN_ECS_COMPONENT_ARRAY_HPP

#include <unordered_map>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/ECS/IComponentArray.hpp"
#include "Acorn/ECS/EntityID.hpp"
#include "Acorn/Templates/ArrayList.hpp"

namespace Acorn::ECS
{
    template<typename T>
    class ENGINE_API ComponentArray final : public IComponentArray
    {
    public:
        ComponentArray();

        void add   (EntityID id, T component);
        bool has   (EntityID id);
        T*   get   (EntityID id);
        void remove(EntityID id);

        const ArrayList<T>& getDense() const noexcept;
        const ArrayList<EntityID>& getDenseToEntity() const noexcept;

    private:
        ArrayList<T>                         m_dense;
        ArrayList<EntityID>                  m_denseToEntity;
        std::unordered_map<EntityID, size_t> m_sparse;
    };
}

#include "Acorn/ECS/ComponentArray.ipp"

#endif /* ACORN_ECS_COMPONENT_ARRAY_HPP */
