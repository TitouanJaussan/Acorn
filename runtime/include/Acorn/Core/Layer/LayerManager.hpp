#ifndef ACORN_LAYER_MANAGER_HPP
#define ACORN_LAYER_MANAGER_HPP

#include <type_traits>
#include <typeindex>
#include <map>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/Logging/LoggerFactory.hpp"
#include "Acorn/Base/Logging/Logger.hpp"
#include "Acorn/Core/Layer/Layer.hpp"
#include "Acorn/Templates/UniquePtr.hpp"

namespace Acorn::Core
{
    template<typename T>
    concept LayerT = std::is_base_of_v<Layer, T>;

    class ENGINE_API LayerManager final
    {
    public:
        LayerManager(Base::LoggerFactory& factory);
        ~LayerManager();

        template<LayerT T, typename... Args>
        void pushLayer(Args&&... args);

    private:
        Base::Logger m_logger;

        std::map<std::type_index, UniquePtr<Layer>> m_layersStack{};
    };
}

#include "Acorn/Core/Layer/LayerManager.ipp"

#endif /* ACORN_LAYER_MANAGER_HPP */
