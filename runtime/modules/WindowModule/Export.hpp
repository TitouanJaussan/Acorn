#ifndef WINDOW_MODULE_EXPORT_HPP
#define WINDOW_MODULE_EXPORT_HPP

#ifdef _WIN32
    #ifdef WINDOWMODULE_BUILD_DLL
        #define WINDOW_MODULE_EXPORT __declspec(dllexport)
    #else
        #define WINDOW_MODULE_EXPORT __declspec(dllimport)
    #endif
    #define WINDOW_MODULE_LOCAL
#else
    #define WINDOW_MODULE_EXPORT __attribute__((visibility("default")))
    #define WINDOW_MODULE_LOCAL __attribute__((visibility("hidden")))
#endif /* _WIN32 */

#endif /* WINDOW_MODULE_EXPORT_HPP */
