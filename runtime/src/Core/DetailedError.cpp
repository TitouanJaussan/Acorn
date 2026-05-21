#include "Acorn/Core/DetailedError.hpp"

namespace Acorn::Core
{
    DetailedError::DetailedError(std::string title, const char* msg)
        : std::runtime_error(msg),
          m_title(title)
    {}

    tui::Block DetailedError::detailedWhat() const
    {
        tui::Block block = tui::text(std::string(what()));

        return tui::border(block);
    }
}
