#ifndef ACORN_ASSERT_HPP
#define ACORN_ASSERT_HPP

#include <cstdlib>
#include <cstdio>

#if defined(ACORN_DEV) || defined(ACORN_DEBUG)
    #define ACORN_ASSERT(expr) do {                  \
        if (!static_cast<bool>(expr))                \
        {                                            \
            fprintf(stderr,                          \
                "Assertion failed: %s\nat %s:%d\n",  \
                #expr,                               \
                __FILE__, __LINE__);                 \
            fflush(stderr);                          \
            std::abort();                            \
        }                                            \
    } while (0)
#else
    #define ACORN_ASSERT(expr)
#endif

#endif /* ACORN_ASSERT_HPP */
