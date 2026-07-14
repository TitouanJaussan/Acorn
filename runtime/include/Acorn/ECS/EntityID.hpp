#ifndef ACORN_ECS_ENTITY_ID_HPP
#define ACORN_ECS_ENTITY_ID_HPP

#include <cstdint>
#include <functional>

#include "Acorn/EngineAPI.hpp"

namespace Acorn::ECS
{
    // If ever performance is a bottleneck a tiny optimization here
    // would be to pack everything in a uint64_t, better hashing and faster op==
    // But bitshift for getting version, and no designated initializer :(
    struct ENGINE_API EntityID
    {
        uint32_t index;
        uint32_t generation;

        bool operator==(const EntityID& other) const noexcept;
    };
}


namespace std
{
    template <>
    struct hash<Acorn::ECS::EntityID>
    {
        std::size_t operator()(const Acorn::ECS::EntityID& id) const noexcept
        {
            return std::hash<uint32_t>{}(id.index); // juste l'index, c'est OK
        }
    };
}

#endif /* ACORN_ECS_ENTITY_ID_HPP */
