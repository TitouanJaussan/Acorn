#ifndef ACORN_UNIT_TEST_HPP
#define ACORN_UNIT_TEST_HPP

namespace Acorn
{
    struct UnitTestResult
    {
        const bool success;
    };

    using TestFn = bool(*)();

    struct UnitTest
    {
        const char* name;
        const TestFn testFn;

        UnitTestResult run() const;
    };
}

#endif /* ACORN_UNIT_TEST_HPP */
