#ifndef ACORN_ARRAYLIST_HPP
#define ACORN_ARRAYLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>

#include "Acorn/EngineAPI.hpp"

namespace Acorn
{
    template<typename T>
    class ENGINE_API ArrayList
    {
    public:
        ArrayList() noexcept;
        ArrayList(const ArrayList& other);    // Copy ctr
        ArrayList(ArrayList&& other);         // Move ctr
        ArrayList(std::initializer_list<T> list);
        ArrayList(T* data, size_t size);
        
        ~ArrayList();

        /* Iterator */
        struct Iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;  // or also value_type*
            using reference         = T&;  // or also value_type&
            
            Iterator(pointer ptr) : m_ptr(ptr) {};

            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }

            // Prefix & postfix increment
            Iterator& operator++() { m_ptr++; return *this; }  
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
            
            Iterator operator-(int val) { m_ptr -= val; return *this; }
            Iterator operator+(int val) { m_ptr += val; return *this; }

            friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        private:
            pointer m_ptr;
        };
        
        [[nodiscard]] T& operator[](size_t i) noexcept;
        [[nodiscard]] const T& operator[](size_t i) const noexcept;

        ArrayList& operator=(ArrayList&& other); // Steal >:)
        ArrayList& operator=(const ArrayList& other); // Copy :(

        Iterator begin() const { return Iterator(&m_arr[0]); }
        Iterator end()   const { return Iterator(&m_arr[m_size]); }

        T& append(const T& val);
        T& append(T&& val);
        void popBack();
        
        template<typename... Args>
        void emplaceBack(Args&&... args);  // Emplaces, but at the end of the list

        void insert(size_t index, T val);
        void insert(size_t pos, Iterator first, Iterator last);

        void swap(size_t idxA, size_t idxB);

        template<typename Fn, typename... Args>
        size_t findIndex(Fn&& findFn, Args&&... args) const;

        [[nodiscard]] size_t getCapacity() const noexcept;
        [[nodiscard]] size_t getSize() const noexcept;
        [[nodiscard]] T* getData() const noexcept;

        [[nodiscard]] bool isEmpty() const noexcept;

        void setCapacity(size_t newCapacity);

        void clearAll();

    protected:
        void growCapacity();
        void destructAll();
        void destroyInternalArray();

    protected:
        T* m_arr{nullptr};

        size_t m_size{0};
        size_t m_capacity{0};
    };
}

#include "Acorn/Templates/ArrayList.ipp"

#endif /* ACORN_ARRAYLIST_HPP */
