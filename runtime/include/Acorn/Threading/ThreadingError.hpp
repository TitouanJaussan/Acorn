#ifndef ACORN_THREADING_ERROR_HPP
#define ACORN_THREADING_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/DetailedError.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Threading
{
    class ENGINE_API ThreadingError final : public Base::DetailedError
    {
    public:
        ThreadingError(String msg);
    };
}

#endif /* ACORN_THREADING_ERROR_HPP */
