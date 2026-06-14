#include "Acorn/Templates/String.hpp"

inline auto fmt::formatter<Acorn::String>::format(const Acorn::String& str,
    format_context& ctx) const
    -> format_context::iterator
{
    return formatter<string_view>::format(str.getData(), ctx);
}

inline constexpr auto std::formatter<Acorn::String>::parse(std::format_parse_context& ctx)
{
    return ctx.begin(); // No specific format specifier
}

inline auto std::formatter<Acorn::String>::format(const Acorn::String& str,
        std::format_context& ctx) const
{
    return std::format_to(ctx.out(), "{}", str.getData());
}
