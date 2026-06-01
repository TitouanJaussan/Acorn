#include "UnitTester.hpp"

#include "tests/RuntimeTests.hpp"

int main()
{
    Acorn::UnitTester tester{};

    Acorn::addRuntimeTests(tester);

    tester.runTests();

    return 0;
}
