#pragma once

#include <EASTL/internal/config.h>

#include <EASTL/allocator.h>

#include <memory>
#include <type_traits>
#include <utility>


namespace std::ea {

template <class StdAllocator, class = void>
class allocator_adapter
{
    // TODO
};

template <class StdAllocator>
class allocator_adapter<StdAllocator, std::void_t<std::declval<StdAllocator&>().get_eastl_allocator()>>
    : protected StdAllocator
{
    typedef StdAllocator base_type;

public:
    EA_CPP20_CONSTEXPR allocator_adapter() EA_CPP11_NOEXCEPT_THROW {}
    EA_CPP20_CONSTEXPR allocator_adapter(const StdAllocator& alloc) EA_CPP11_NOEXCEPT_THROW
        : base_type(alloc)
    {}
    EA_CPP20_CONSTEXPR allocator_adapter(const allocator_adapter& other) EA_CPP11_NOEXCEPT_THROW
        : base_type(other.get_std_allocator())
    {}

    void* allocate(size_t n, int flags = 0) {
        return get_eastl_allocator().allocate(n, flags);
    }
    void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0) {
        return get_eastl_allocator().allocate(n, alignment, offset, flags);
    }
    void deallocate(void* p, size_t n) {
        get_eastl_allocator().deallocate(p, n);
    }

    const char* get_name() const {
        return get_eastl_allocator().get_name();
    }
    void set_name(const char* pName) {
        get_eastl_allocator().set_name(pName);
    }

    constexpr StdAllocator& get_std_allocator() noexcept { return *this; }
    constexpr const StdAllocator& get_std_allocator() const noexcept { return *this; }
};

template <class T1, class T2>
constexpr bool operator==(const allocator_adapter<T1>& a, const allocator_adapter<T2>& b) noexcept
{
    return a.get_std_allocator() == b.get_std_allocator();
}
#if __cplusplus < 202002L
template <class T1, class T2>
constexpr bool operator!=(const allocator_adapter<T1>& a, const allocator_adapter<T2>& b) noexcept
{
    return a.get_std_allocator() != b.get_std_allocator();
}
#endif

}  // namespace std::ea
