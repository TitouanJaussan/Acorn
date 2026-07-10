#include "Layers/ProjectSelectionLayer.hpp"

namespace Acorn::Editor
{
    ProjectSelectionLayer::ProjectSelectionLayer(
        Base::LoggerFactory loggerFactory)
        : m_logger(loggerFactory.create(
            "ProjectSelectionLayer"))
    {}

    void ProjectSelectionLayer::onAttach()
    {
    }

    void ProjectSelectionLayer::onDetach()
    {
    }
}
