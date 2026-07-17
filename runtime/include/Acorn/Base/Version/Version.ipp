#pragma once

#include "Acorn/Base/Version/Version.hpp"

inline constexpr auto fmt::formatter<Acorn::Version::Version>::parse(
    fmt::format_parse_context& ctx) const
{
    return ctx.begin();
}

template<typename FormatContext>
inline auto fmt::formatter<Acorn::Version::Version>::format(
    const Acorn::Version::Version& ver,
    FormatContext& ctx) const
{
    return fmt::formatter<Acorn::String>(ver.string(), ctx);
}

inline constexpr auto std::formatter<Acorn::Version::Version>::parse(
    std::format_parse_context& ctx)
{
    return ctx.begin();
}

inline auto std::formatter<Acorn::Version::Version>::format(
    const Acorn::Version::Version& ver,
    std::format_context& ctx) const
{
    return std::format_to(ctx.out(), "{}", ver.string());
}
