#include "Acorn/Module/ModuleError.hpp"

namespace Acorn::Module
{
    ModuleError::ModuleError(String msg)
        : Base::DetailedError("Module", std::move(msg))
    {}
}
