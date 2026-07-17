#ifndef SCENE_MODULE_EXPORT_HPP
#define SCENE_MODULE_EXPORT_HPP

#ifdef _WIN32
    #ifdef SCENEMODULE_BUILD_DLL
        #define SCENE_MODULE_EXPORT __declspec(dllexport)
    #else
        #define SCENE_MODULE_EXPORT __declspec(dllimport)
    #endif
    #define SCENE_MODULE_LOCAL
#else
    #define SCENE_MODULE_EXPORT __attribute__((visibility("default")))
    #define SCENE_MODULE_LOCAL __attribute__((visibility("hidden")))
#endif /* _WIN32 */

#endif /* SCENE_MODULE_EXPORT_HPP */
