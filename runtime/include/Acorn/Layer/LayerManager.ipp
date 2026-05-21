#pragma once

#include "Acorn/Layer/LayerManager.hpp"

#include <Acorn/Core/Assert.hpp>

namespace Acorn
{
    template<LayerT T, typename... Args>
    void LayerManager::pushLayer(Args&&... args)
    {
        const std::type_index id = typeid(T);
        ACORN_ASSERT(!m_layersStack.contains(id));

        auto& layer = m_layersStack[id] =
            std::make_unique<T>(std::forward<Args>(args)...);

        layer->onAttach();
    }
}
