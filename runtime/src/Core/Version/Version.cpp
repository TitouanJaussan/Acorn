#include "Acorn/Core/Version/Version.hpp"
#include "Acorn/Core/Version/VersionError.hpp"
#include "Acorn/Core/Format.hpp"

namespace Acorn::Version
{
    Version::Version(ArrayList<int64_t> version)
    {
        if (version.getSize() != 3)
            throw VersionError(Core::format(
                "Invalid version array size: {}"
                "(expected 3: major, minor, version)",
                version.getSize()));

        m_major = version[0];
        m_minor = version[1];
        m_patch = version[2];
    }
}
