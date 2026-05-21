#ifndef ACORN_APPLICATION_HPP
#define ACORN_APPLICATION_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Runtime.hpp"

namespace Acorn::Core
{
    class ENGINE_API Application
    {
    public:
        Application(int argc, const char** argv);

        void launch();
    
    protected:
        Core::Runtime m_runtime;
    };
}

#endif /* ACORN_APPLICATION_HPP */
