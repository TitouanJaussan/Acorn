#ifndef ACORN_ASSERT_HPP
#define ACORN_ASSERT_HPP

#include <cstdlib>

// TODO: Log message
#if defined(ACORN_DEV) || defined(ACORN_DEBUG)
    #define ACORN_ASSERT(expr) do { \
        if (!static_cast<bool>(expr))\
        {\
            std::abort();\
        }\
    } while (0)
#else
    #define ACORN_ASSERT(expr)
#endif

#endif /* ACORN_ASSERT_HPP */
