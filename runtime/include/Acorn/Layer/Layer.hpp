#ifndef ACORN_LAYER_HPP
#define ACORN_LAYER_HPP

#include "Acorn/EngineAPI.hpp"

namespace Acorn
{
    class ENGINE_API Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() {};

        virtual void onAttach() {};
        virtual void onDetach() {};
    };
}

#endif /* ACORN_LAYER_HPP */
