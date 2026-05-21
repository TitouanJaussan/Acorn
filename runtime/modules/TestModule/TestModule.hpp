#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

#ifdef _WIN32
    #ifdef TESTMODULE_BUILD_DLL
        #define API __declspec(dllexport)
    #else
        #define API
    #endif
#else
    #define API __attribute__((visibility("default")))
#endif /* _WIN32 */

extern "C"
{
    void API load();
    void API update();
    void API render();
    void API unload();

    extern const char name[];
}

#endif /* TEST_MODULE_HPP */
