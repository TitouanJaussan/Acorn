#ifndef ACORN_APPLICATION_HPP
#define ACORN_APPLICATION_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Core/Runtime/Engine.hpp"
#include "Acorn/Templates/UniquePtr.hpp"

namespace Acorn::Core
{
    class ENGINE_API Application
    {
    public:
        Application(int argc, char** argv);

        void launch();
    
    protected:
        void tidyUp();

        UniquePtr<Runtime::Engine> m_engine;
    };
}

#endif /* ACORN_APPLICATION_HPP */
