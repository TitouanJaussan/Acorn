#include "Acorn/Filesystem/File.hpp"
#include "Acorn/Core/Assert.hpp"

namespace Acorn::Filesystem
{
    File::File(File&& other)
        : m_path(std::move(other.m_path)),
          m_content(std::move(other.m_content))
    {}

    File::File(const File& other)
        : m_path(other.m_path),
          m_content(other.m_content)
    {}

    char* File::getData() const noexcept
    {
        return m_content.getData();
    }

    File::File(std::filesystem::path path,
               ArrayList<char> content)
        : m_path(std::move(path)),
          m_content{std::move(content)}
    {
        ACORN_ASSERT(std::filesystem::is_regular_file(m_path));
    }
}
