#ifndef ACORN_FILESYSTEM_ERROR_HPP
#define ACORN_FILESYSTEM_ERROR_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Base/DetailedError.hpp"

namespace Acorn::Filesystem
{
    class ENGINE_API FilesystemError final : public Base::DetailedError
    {
    public:
        FilesystemError(String msg);
    };
}

#endif /* ACORN_FILESYSTEM_ERROR_HPP */
