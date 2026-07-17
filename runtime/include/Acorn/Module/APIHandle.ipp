#pragma once

#include "Acorn/Module/APIHandle.hpp"

namespace Acorn::Module
{
    template<typename ApiT>
    APIHandle<ApiT>::APIHandle(ModuleAPI* handle) noexcept
        : m_handle(handle)
    {}

    template<typename ApiT>
    template<typename T>
    APIHandle<ApiT>::APIHandle(APIHandle<T> handle) noexcept
        : m_handle(handle.m_handle)
    {}

    template<typename ApiT>
    ApiT* APIHandle<ApiT>::operator->() const noexcept
    {
        return static_cast<ApiT*>(m_handle->modAPI);
    }
}
