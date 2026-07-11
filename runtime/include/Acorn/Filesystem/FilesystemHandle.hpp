#ifndef ACORN_FILESYSTEM_HANDLE_HPP
#define ACORN_FILESYSTEM_HANDLE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Filesystem/File.hpp"

namespace Acorn::Filesystem
{
    class Filesystem;

    class ENGINE_API FilesystemHandle final
    {
    public:
        FilesystemHandle(Filesystem& handle);

        File readFile(std::filesystem::path path,
                      bool nullTerminated = false);

    private:
        Filesystem& m_handle;
    };
}

#endif /* ACORN_FILESYSTEM_HANDLE_HPP */
