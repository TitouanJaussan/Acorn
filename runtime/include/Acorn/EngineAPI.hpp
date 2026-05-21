#ifndef ACORN_ENGINE_API_HPP
#define ACORN_ENGINE_API_HPP

#ifdef _WIN32
    #ifdef ENGINE_BUILD_DLL
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif /* ENGINE_BUILD_DLL */
#else
    #define ENGINE_API __attribute__((visibility("default")))
#endif /* _WIN32 */

#endif /* ACORN_ENGINE_API_HPP */
