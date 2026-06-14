#include "Acorn/Threading/ThreadingError.hpp"

namespace Acorn::Threading
{
    ThreadingError::ThreadingError(String msg)
        : Core::DetailedError("ThreadingError", std::move(msg))
    {}
}
