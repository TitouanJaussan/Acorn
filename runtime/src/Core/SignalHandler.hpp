#ifndef ACORN_SIGNAL_HANDLER_HPP
#define ACORN_SIGNAL_HANDLER_HPP

#include "Acorn/Core/Runtime/Runtime.hpp"

namespace Acorn::Core
{
    void setSignalHandler(Acorn::Core::Runtime* runtime);
}

#endif /* ACORN_SIGNAL_HANDLER_HPP */
