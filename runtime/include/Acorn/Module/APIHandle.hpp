#ifndef MODULE_API_HANDLE_HPP
#define MODULE_API_HANDLE_HPP

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Module/ModuleAPI.hpp"

namespace Acorn::Module
{
    template<typename ApiT = void>
    class ENGINE_API APIHandle
    {
    public:
        explicit APIHandle(ModuleAPI* handle) noexcept;
        
        template<typename T>
        APIHandle(APIHandle<T> handle) noexcept;

        ApiT* operator->() const noexcept;

        template<typename T>
        friend class APIHandle;

    private:
        ModuleAPI* m_handle;
    };
}

#include "Acorn/Module/APIHandle.ipp"

#endif /* MODULE_API_HANDLE_HPP */
