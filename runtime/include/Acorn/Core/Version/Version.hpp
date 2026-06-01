#ifndef ACORN_VERSION_HPP
#define ACORN_VERSION_HPP

#include <cstdint>
#include <string>
#include <format>

#include "Acorn/EngineAPI.hpp"

namespace Acorn::Version
{
    class ENGINE_API Version
    {
        public:
            constexpr Version() noexcept = default;
            constexpr Version(const Version&) = default;
            constexpr Version(Version&&) = default;
    
            constexpr Version(const uint32_t major, const uint32_t minor, const uint32_t patch) noexcept
                : m_major(major),
                  m_minor(minor),
                  m_patch(patch)
            {}

            constexpr uint32_t major() const noexcept { return m_major; }
            constexpr uint32_t minor() const noexcept { return m_minor; }
            constexpr uint32_t patch() const noexcept { return m_patch; }

            std::string string() const { return std::format("v{}.{}.{}", m_major, m_minor, m_patch); }

            constexpr bool operator<=>(const Version&) const = default;
            explicit operator std::string() const { return string(); }

        private:
            uint32_t m_major{0};
            uint32_t m_minor{0};
            uint32_t m_patch{0};
    };
}

#endif /* ACORN_VERSION_HPP */
