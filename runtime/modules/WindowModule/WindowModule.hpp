#ifndef WINDOW_MODULE_HPP
#define WINDOW_MODULE_HPP

#ifdef _WIN32
    #ifdef TESTMODULE_BUILD_DLL
        #define API __declspec(dllexport)
    #else
        #define API
    #endif
#else
    #define API __attribute__((visibility("default")))
#endif /* _WIN32 */

#include <Acorn/Core/Logging/Logger.hpp>

extern "C"
{
    void API load(Acorn::Core::Logger providedLogger);
    void API update();
    void API render();
    void API unload();

    extern const char name[];
}

#endif /* WINDOW_MODULE_HPP */
