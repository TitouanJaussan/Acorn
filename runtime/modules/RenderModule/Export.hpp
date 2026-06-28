#ifndef RENDER_MODULE_EXPORT_HPP
#define RENDER_MODULE_EXPORT_HPP

#ifdef _WIN32
    #ifdef RENDERMODULE_BUILD_DLL
        #define RENDER_MODULE_EXPORT __declspec(dllexport)
    #else
        #define RENDER_MODULE_EXPORT __declspec(dllimport)
    #endif
    #define RENDER_MODULE_LOCAL
#else
    #define RENDER_MODULE_EXPORT __attribute__((visibility("default")))
    #define RENDER_MODULE_LOCAL __attribute__((visibility("hidden")))
#endif /* _WIN32 */

#endif /* RENDER_MODULE_EXPORT_HPP */
