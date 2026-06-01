#include <iostream>
#include <format>

#include "UnitTester.hpp"

namespace Acorn
{
    std::string colorString(std::string str, AnsiColor col)
    {
        return std::format(
            "\033[{}m{}\033[0m",
            std::to_string(static_cast<int>(col)),
            str
        );
    }

    void UnitTester::addTest(UnitTest test)
    {
        m_tests.emplace_back(test);
    }

    void UnitTester::runTests()
    {
        std::cout << std::format(
            "Running tests ({})...",
            m_tests.size()
        )<< std::endl;

        const auto successStr = colorString("success", AnsiColor::Green);
        const auto failureStr = colorString("failure", AnsiColor::Red);

        for (UnitTest& test: m_tests)
        {
            const auto result = test.run();
            std::cout << std::format(
                "{}: {}",
                test.name,
                result.success ? successStr : failureStr
            ) << std::endl;
        }
    }
}
