#ifndef ACORN_UNIT_TESTER_HPP
#define ACORN_UNIT_TESTER_HPP

#include <vector>
#include <string>

#include "UnitTest.hpp"

namespace Acorn
{
    enum class AnsiColor
    {
        Black = 30,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White
    };

    std::string colorString(std::string str, AnsiColor col);

    class UnitTester
    {
    public:
        UnitTester() = default;

        void addTest(UnitTest test);

        void runTests();

    private:
        std::vector<UnitTest> m_tests;
    };
}

#endif /* ACORN_UNIT_TESTER_HPP */
