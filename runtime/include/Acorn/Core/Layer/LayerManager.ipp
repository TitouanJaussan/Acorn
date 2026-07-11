#pragma once

#include <utility>

#include "Acorn/Core/Layer/LayerManager.hpp"
#include "Acorn/Base/Assert.hpp"

namespace Acorn::Core
{
    template<LayerT T, typename... Args>
    void LayerManager::pushLayer(Args&&... args)
    {
        const std::type_index id = typeid(T);
        ACORN_ASSERT(!m_layersStack.contains(id));

        // TODO: Replace with Pair when possible
        m_layersStack.emplace(std::make_pair(
            id,
            UniquePtr<T>::create(std::forward<Args>(args)...)
        ));

        m_layersStack[id]->onAttach();
    }
}
