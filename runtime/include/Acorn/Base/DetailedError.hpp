#ifndef ACORN_DETAILED_ERROR_HPP
#define ACORN_DETAILED_ERROR_HPP

#include <stdexcept>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/String.hpp"
#include "tui/tblocks.hpp"

namespace Acorn::Base
{
    class ENGINE_API DetailedError :
        public std::runtime_error
    {
    public:
        DetailedError(String title, String msg);

        tui::Block detailedWhat() const;

    private:
        const String m_title;
    };
}

#endif /* ACORN_DETAILED_ERROR_HPP */
