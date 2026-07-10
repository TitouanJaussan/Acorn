#include "Acorn/Base/Version/Version.hpp"
#include "Acorn/Base/Version/VersionError.hpp"
#include "Acorn/Base/Format.hpp"

namespace Acorn::Version
{
    Version::Version(ArrayList<int64_t> version)
    {
        if (version.getSize() != 3)
            throw VersionError(Base::format(
                "Invalid version array size: {}"
                "(expected 3: major, minor, version)",
                version.getSize()));

        m_major = version[0];
        m_minor = version[1];
        m_patch = version[2];
    }

    String Version::string() const
    {
        return Base::format("v{}.{}.{}", m_major, m_minor, m_patch);
    }
}
