#include "Acorn/DynamicLib/DynamicLibraryError.hpp"

namespace Acorn::Lib
{
    DynamicLibraryError::DynamicLibraryError(String msg)
        : Base::DetailedError("DynamicLibrary", std::move(msg))
    {}
}
