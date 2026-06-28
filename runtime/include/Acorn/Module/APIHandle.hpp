#ifndef MODULE_API_HANDLE_HPP
#define MODULE_API_HANDLE_HPP

namespace Acorn::Module
{
    class APIHandle
    {
    public:
        explicit APIHandle(void* apiPtr);

        template<typename ApiT>
        ApiT* as() const;

    private:
        void update(void* newApiPtr);

    private:
        void* m_apiPtr;

        friend class ModuleRegistry;
    };
}

#include "Acorn/Module/APIHandle.ipp"

#endif /* MODULE_API_HANDLE_HPP */
