#ifndef RENDER_MODULE_API_HPP
#define RENDER_MODULE_API_HPP

#ifdef _WIN32
    #ifdef RENDERMODULE_BUILD_DLL
        #define API __declspec(dllexport)
    #else
        #define API
    #endif
    #define API_PRIVATE 
#else
    #define API __attribute__((visibility("default")))
    #define API_PRIVATE __attribute__((visibility("hidden")))
#endif /* _WIN32 */

#endif /* RENDER_MODULE_API_HPP */
