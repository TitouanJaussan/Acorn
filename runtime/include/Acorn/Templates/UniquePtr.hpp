#ifndef ACORN_UNIQUE_PTR_HPP
#define ACORN_UNIQUE_PTR_HPP

#include <type_traits>

#include "Acorn/EngineAPI.hpp"

namespace Acorn
{
    template<typename T>
    class ENGINE_API UniquePtr
    {
    public:
        UniquePtr() noexcept;
        UniquePtr(UniquePtr&& other) noexcept;
        UniquePtr(const UniquePtr& other);
        
        template<typename OtherT>
        requires(std::is_base_of_v<T, OtherT>)
        UniquePtr(UniquePtr<OtherT>&& other);

        UniquePtr(T* ptr) noexcept;
        ~UniquePtr();

        T* operator->() const noexcept;
        T& operator*() const noexcept;

        UniquePtr<T>& operator=(UniquePtr<T>&& other);
        UniquePtr<T>& operator=(const UniquePtr<T>& other);
        bool operator!() const noexcept;

        T* getPtr() const noexcept;
        void reset();

        template<typename... Args>
        static UniquePtr<T> create(Args&&... args);

        template<typename OtherT>
        friend class UniquePtr;

    private:
        T* m_ptr{nullptr};
    };
}

#include "Acorn/Templates/UniquePtr.ipp"

#endif /* ACORN_UNIQUE_PTR_HPP */
