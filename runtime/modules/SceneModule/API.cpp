#include "API.hpp"

SceneModuleAPI::SceneModuleAPI(SceneModule* mod)
    : m_mod(mod)
{}

void SceneModuleAPI::getRenderDataSnapshot()
{
    m_mod->logger.info("Retrieved render data snapshot !");
}
