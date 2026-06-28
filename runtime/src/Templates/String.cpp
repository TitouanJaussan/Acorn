#include <cstring>

#include "Acorn/Templates/String.hpp"

namespace Acorn
{
    String::String() noexcept
        : m_str()
    {}

    String::String(const char* str)
        : m_str()
    {
        const size_t len = strlen(str) + 1;
        m_str.setCapacity(len);
        m_str.insert(
            0,
            ArrayList<char>::Iterator(const_cast<char*>(str)),
            ArrayList<char>::Iterator(const_cast<char*>(str + len))
        );
    }

    String::String(String&& other)
        : m_str(std::move(other.m_str))
    {}

    String::String(const String& other)
        : m_str(other.m_str)
    {}

    String& String::operator=(String&& other)
    {
        m_str = std::move(other.m_str);

        return *this;
    }

    String& String::operator=(const String& other)
    {
        m_str = other.m_str;

        return *this;
    }

    String& String::operator+=(String&& other)
    {
        m_str.setCapacity(m_str.getSize() + other.getSize());
        m_str.insert(
            getSize(),
            other.m_str.begin(),
            other.m_str.end() - 1
        );

        return *this;
    }

    String& String::operator+=(const String& other)
    {
        m_str.setCapacity(m_str.getSize() + other.getSize());
        m_str.insert(
            getSize(),
            other.m_str.begin(),
            other.m_str.end() - 1
        );

        return *this;
    }

    String String::operator+(String&& other) const
    {
        String out{};
        out.m_str.setCapacity(getSize() + other.getSize());

        out.m_str.insert(
            0,
            m_str.begin(),
            m_str.end());

        out.m_str.insert(
            getSize(),
            other.m_str.begin(),
            other.m_str.end());

        return out;
    }

    String String::operator+(const String& other) const
    {
        String out{};
        out.m_str.setCapacity(getSize() + other.getSize());

        out.m_str.insert(
            0,
            m_str.begin(),
            m_str.end());

        out.m_str.insert(
            getSize(),
            other.m_str.begin(),
            other.m_str.end());

        return out;
    }

    bool String::operator==(const String& other) const
    {
        return strcmp(m_str.getData(), other.getData()) == 0;
    }

    void String::append(char c)
    {
        if (m_str.getSize() == 0)
        {
            m_str.setCapacity(2);
            m_str.append(c);
        }
        else
            m_str[getSize()] = c;

        m_str.append('\0');
    }

    String String::substring(size_t startIndex, size_t len)
    {
        String newStr{};
        newStr.m_str.setCapacity(len + 1);

        memcpy(newStr.getData(),
               m_str.getData() + startIndex,
               (len + 1) * sizeof(char));


        return newStr;
    }

    size_t String::getSize() const noexcept
    {
        if (m_str.getSize() == 0)
            return 0;

        return m_str.getSize() - 1;
    }

    char* String::getData() const noexcept
    {
        return m_str.getData();
    }

    size_t String::getHash() const noexcept
    {
        std::size_t hash = 14695981039346656037ULL; // offset basis
        for (std::size_t i = 0; i < getSize(); ++i)
        {
            hash ^= static_cast<unsigned char>(m_str[i]);
            hash *= 1099511628211ULL;               // FNV prime
        }
        return hash;
    }
}

