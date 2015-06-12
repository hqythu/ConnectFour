#ifndef SINGLETON_POOL_H_
#define SINGLETON_POOL_H_

#include "MemoryPool.h"

template <typename T>
class SingletonPool
{
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef const T*        const_pointer;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
    typedef std::false_type propagate_on_container_copy_assignment;
    typedef std::true_type  propagate_on_container_move_assignment;
    typedef std::true_type  propagate_on_container_swap;

    template <typename U> struct rebind {
      typedef SingletonPool<U> other;
    };

    SingletonPool() noexcept {}

    ~SingletonPool() noexcept {}

    pointer address(reference x) const noexcept
    {
        return pool.address(x);
    }

    const_pointer address(const_reference x) const noexcept
    {
        return pool.address(x);
    }

    // Can only allocate one object at a time. n and hint are ignored
    pointer allocate(size_type n = 1, const_pointer hint = 0)
    {
        return pool.allocate(n, hint);
    }

    void deallocate(pointer p, size_type n = 1)
    {
        pool.deallocate(p, n);
    }

    size_type max_size() const noexcept
    {
        return pool.max_size();
    }

    template <class U, class... Args> void construct(U* p, Args&&... args)
    {
        pool.construct(p, std::forward<Args>(args)...);
    }

    template <class U> void destroy(U* p)
    {
        pool.destroy(p);
    }

private:
    static MemoryPool<T> pool;
};


template<typename T>
MemoryPool<T> SingletonPool<T>::pool;


#endif // SINGLETON_POOL_H_