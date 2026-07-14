#include "Acorn/ECS/EntityID.hpp"

namespace Acorn::ECS
{
    bool EntityID::operator==(const EntityID& other) const noexcept
    {
        return index == other.index && generation == other.generation;
    }
}
