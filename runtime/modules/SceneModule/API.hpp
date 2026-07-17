#ifndef SCENE_MODULE_API_HPP
#define SCENE_MODULE_API_HPP

#include "Export.hpp"
#include "SceneModule.hpp"

class SCENE_MODULE_EXPORT SceneModuleAPI
{
public:
    SceneModuleAPI(SceneModule* mod);

    void getRenderDataSnapshot();

private:
    SceneModule* m_mod;
};

#endif /* SCENE_MODULE_API_HPP */
