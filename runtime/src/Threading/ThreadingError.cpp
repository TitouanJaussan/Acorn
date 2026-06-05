#include "Acorn/Threading/ThreadingError.hpp"

namespace Acorn::Threading
{
    ThreadingError::ThreadingError(std::string msg)
        : Core::DetailedError("ThreadingError", std::move(msg))
    {}
}
