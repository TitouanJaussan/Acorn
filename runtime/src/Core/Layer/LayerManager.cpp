#include "Acorn/Core/Layer/LayerManager.hpp"

namespace Acorn::Core
{
    LayerManager::LayerManager(Base::LoggerFactory& factory)
        : m_logger(factory.create("LayerManager"))
    {}

    LayerManager::~LayerManager()
    {
        for (auto it = m_layersStack.rbegin();
             it != m_layersStack.rend(); ++it)
        {
            it->second->onDetach();
        }
    }
}
