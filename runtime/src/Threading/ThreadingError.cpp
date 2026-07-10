#include "Acorn/Threading/ThreadingError.hpp"

namespace Acorn::Threading
{
    ThreadingError::ThreadingError(String msg)
        : Base::DetailedError("ThreadingError", std::move(msg))
    {}
}
