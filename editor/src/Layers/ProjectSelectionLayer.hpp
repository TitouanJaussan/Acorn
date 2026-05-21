#ifndef ACORN_PROJECT_SELECTION_LAYER_HPP
#define ACORN_PROJECT_SELECTION_LAYER_HPP

#include <Acorn/Layer/Layer.hpp>
#include <Acorn/Core/Logging/LoggerFactory.hpp>

namespace Acorn::Editor
{
    class ProjectSelectionLayer final : public Layer
    {
    public:
        ProjectSelectionLayer(Core::LoggerFactory loggerFactory);

        void onAttach() override;
        void onDetach() override;
    private:
        Core::Logger m_logger;
    };
}

#endif /* ACORN_PROJECT_SELECTION_LAYER_HPP */
