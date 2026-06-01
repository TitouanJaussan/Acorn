#include "UnitTest.hpp"

namespace Acorn
{
    UnitTestResult UnitTest::run() const
    {
        return UnitTestResult
        {
            .success = testFn()
        };
    }
}
