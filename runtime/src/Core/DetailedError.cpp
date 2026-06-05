#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Core
{
    DetailedError::DetailedError(std::string title, std::string msg)
        : std::runtime_error(std::move(msg)),
          m_title(std::move(title))
    {}

    tui::Block DetailedError::detailedWhat() const
    {
        tui::Block block = tui::text(std::string(what()));

        return tui::border(block);
    }
}
