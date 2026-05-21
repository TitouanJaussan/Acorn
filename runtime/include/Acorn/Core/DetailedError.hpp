#ifndef ACORN_DETAILED_ERROR_HPP
#define ACORN_DETAILED_ERROR_HPP

#include <stdexcept>
#include <string>

#include "Acorn/EngineAPI.hpp"
#include "tui/tblocks.hpp"

namespace Acorn::Core
{
    class ENGINE_API DetailedError :
        public std::runtime_error
    {
    public:
        DetailedError(std::string title, const char* msg);

        tui::Block detailedWhat() const;

    private:
        const std::string m_title;
    };
}

#endif /* ACORN_DETAILED_ERROR_HPP */
