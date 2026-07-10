#ifndef ACORN_SIGNAL_HANDLER_HPP
#define ACORN_SIGNAL_HANDLER_HPP

#include "Acorn/Core/Runtime/Engine.hpp"

namespace Acorn::Core
{
    void setSignalHandler(Acorn::Runtime::Engine* runtime);
}

#endif /* ACORN_SIGNAL_HANDLER_HPP */
