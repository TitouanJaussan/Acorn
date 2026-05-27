#ifndef ACORN_RUNTIME_API_HPP
#define ACORN_RUNTIME_API_HPP

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Core
{
    class Runtime;

    class ENGINE_API RuntimeAPI
    {
    public:
        RuntimeAPI(Runtime& runtime);

        void stopRuntime() const;

    private:
        Runtime& m_runtime;
    };
}

#endif /* ACORN_RUNTIME_API_HPP */
