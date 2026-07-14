#ifndef ACORN_ECS_ENTITY_MANAGER_HPP
#define ACORN_ECS_ENTITY_MANAGER_HPP

#include <cstdint>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/ECS/EntityID.hpp"

namespace Acorn::ECS
{
    class ENGINE_API EntityManager
    {
    public:
        EntityManager();

        EntityID create();
        void     destroy(EntityID id);
        bool     isValid(EntityID id) const;

    private:
        ArrayList<uint32_t> m_generations;
        ArrayList<uint32_t> m_freeIndices;
    };
}

#endif /* ACORN_ECS_ENTITY_MANAGER_HPP */
