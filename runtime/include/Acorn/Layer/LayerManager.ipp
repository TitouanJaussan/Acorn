#pragma once

#include <utility>

#include "Acorn/Layer/LayerManager.hpp"
#include "Acorn/Core/Assert.hpp"

namespace Acorn
{
    template<LayerT T, typename... Args>
    void LayerManager::pushLayer(Args&&... args)
    {
        const std::type_index id = typeid(T);
        ACORN_ASSERT(!m_layersStack.contains(id));

        m_layersStack.emplace(std::make_pair(
            id,
            UniquePtr<Layer>(mem_new<T>(std::forward<Args>(args)...))
        ));

        m_layersStack[id]->onAttach();
    }
}
