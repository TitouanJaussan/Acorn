#include "Acorn/Layer/LayerManager.hpp"

namespace Acorn
{
    LayerManager::~LayerManager()
    {
        for (auto it = m_layersStack.rbegin();
             it != m_layersStack.rend(); ++it)
        {
            it->second->onDetach();
        }
    }
}
