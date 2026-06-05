#ifndef ACORN_THREADING_ERROR_HPP
#define ACORN_THREADING_ERROR_HPP

#include <string>

#include "Acorn/Core/DetailedError.hpp"
#include "Acorn/EngineAPI.hpp"

namespace Acorn::Threading
{
    class ENGINE_API ThreadingError final : public Core::DetailedError
    {
    public:
        ThreadingError(std::string msg);
    };
}

#endif /* ACORN_THREADING_ERROR_HPP */
