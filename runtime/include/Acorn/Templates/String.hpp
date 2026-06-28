#ifndef ACORN_STRING_HPP
#define ACORN_STRING_HPP

#include <fmt/format.h>
#include <format>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"

namespace Acorn
{
    class ENGINE_API String
    {
    public:
        String() noexcept;
        String(const char* str);

        String(String&& other);
        String(const String& other);
        String& operator=(String&& other);
        String& operator=(const String& other);

        String& operator+=(String&& other);
        String& operator+=(const String& other);
        String operator+(String&& other) const;
        String operator+(const String& other) const;

        bool operator==(const String& other) const;

        ~String() = default;

        void   append(char c);
        String substring(size_t startIndex, size_t len);

        size_t getSize() const noexcept;
        char*  getData() const noexcept;
        size_t getHash() const noexcept;

    private:
        ArrayList<char> m_str;
    };
}

template<>
struct fmt::formatter<Acorn::String>: formatter<string_view>
{
    auto format(const Acorn::String& str, format_context& ctx) const
        -> format_context::iterator;
};

template<>
struct std::formatter<Acorn::String>
{
    constexpr auto parse(std::format_parse_context& ctx);
    auto format(const Acorn::String& str, std::format_context& ctx) const;
};

#include "Acorn/Templates/String.ipp"

#endif /* ACORN_STRING_HPP */
