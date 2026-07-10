#ifndef ACORN_PROJECT_SELECTION_LAYER_HPP
#define ACORN_PROJECT_SELECTION_LAYER_HPP

#include <Acorn/Core/Layer/Layer.hpp>
#include <Acorn/Base/Logging/LoggerFactory.hpp>

namespace Acorn::Editor
{
    class ProjectSelectionLayer final : public Core::Layer
    {
    public:
        ProjectSelectionLayer(Base::LoggerFactory loggerFactory);

        void onAttach() override;
        void onDetach() override;
    private:
        Base::Logger m_logger;
    };
}

#endif /* ACORN_PROJECT_SELECTION_LAYER_HPP */
