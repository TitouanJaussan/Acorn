#pragma once

#include <utility>

#include "Acorn/Core/Runtime/Engine.hpp"

namespace Acorn::Runtime
{
    template<Core::LayerT T, typename... Args>
    void Engine::pushLayer(Args&&... args)
    {
        m_core.layerManager.pushLayer<T>(
            std::forward<Args>(args)...);
    }
}
