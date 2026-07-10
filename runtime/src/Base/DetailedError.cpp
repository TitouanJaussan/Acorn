#include <string>

#include "Acorn/Base/DetailedError.hpp"

namespace Acorn::Base
{
    DetailedError::DetailedError(String title, String msg)
        : std::runtime_error(std::string(msg.getData())),
          m_title(std::move(title))
    {}

    tui::Block DetailedError::detailedWhat() const
    {
        tui::Block block = tui::text(std::string(what()));

        return tui::border(block);
    }
}
