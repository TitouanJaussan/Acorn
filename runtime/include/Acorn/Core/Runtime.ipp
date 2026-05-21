#pragma once

#include <utility>

#include "Acorn/Core/Runtime.hpp"

namespace Acorn::Core
{
    template<LayerT T, typename... Args>
    void Runtime::pushLayer(Args&&... args)
    {
        m_layerManager.pushLayer<T>(
            std::forward<Args>(args)...);
    }
}
