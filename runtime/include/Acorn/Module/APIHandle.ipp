#pragma once

#include "Acorn/Module/APIHandle.hpp"

namespace Acorn::Module
{
    template<typename ApiT>
    ApiT* APIHandle::as() const
    {
        return static_cast<ApiT*>(m_apiPtr);
    }
}
