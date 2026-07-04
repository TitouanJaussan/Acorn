#ifndef ACORN_FILE_HPP
#define ACORN_FILE_HPP

#include <filesystem>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"

namespace Acorn::Filesystem
{
    class Filesystem;

    class ENGINE_API File
    {
    public:
        File(File&& other);
        File(const File& other);

        char* getData() const noexcept;

    private:
        friend class Filesystem;

        explicit File(std::filesystem::path filePath,
                      ArrayList<char> content);

    private:
        std::filesystem::path m_path;
        ArrayList<char> m_content;
    };
}

#endif /* ACORN_FILE_HPP */
