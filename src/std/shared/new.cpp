#include <new>

#include <cstdlib>
#include <utility>

namespace std {

nothrow_t const nothrow;

namespace {

[[clang::require_constant_initialization]] new_handler __new_handler;

} // anonymous namespace

new_handler set_new_handler(new_handler handler) noexcept { return exchange(__new_handler, handler); }
new_handler get_new_handler() noexcept { return __new_handler; }

void __throw_bad_alloc() {
#if __has_feature(cxx_exceptions)
    throw bad_alloc();
#else
    std::abort();
#endif
}

} // namespace std

[[gnu::weak]] void* operator new  (std::size_t size) {
    if (size == 0)
        size = 1;
    void* ptr;
    while ((ptr = std::malloc(size)) == nullptr)
        if (auto handler = std::get_new_handler())
            handler();
        else
#if __has_feature(cxx_exceptions)
            throw std::bad_alloc();
#else
            break;
#endif
    return ptr;
}
[[gnu::weak]] void* operator new  (std::size_t size, std::nothrow_t const&) noexcept {
    void* ptr = nullptr;
#if __has_feature(cxx_exceptions)
    try {
#endif
        ptr = ::operator new(size);
#if __has_feature(cxx_exceptions)
    } catch(...) {}
#endif
    return ptr;
}
[[gnu::weak]] void  operator delete  (void* ptr)                        noexcept { std::free(ptr); }
[[gnu::weak]] void  operator delete  (void* ptr, const std::nothrow_t&) noexcept { ::operator delete  (ptr); }
[[gnu::weak]] void  operator delete  (void* ptr, std::size_t)           noexcept { ::operator delete  (ptr); }

[[gnu::weak]] void* operator new[](std::size_t size) { return operator new(size); }
[[gnu::weak]] void* operator new[](std::size_t size, std::nothrow_t const&) noexcept { return operator new(size, std::nothrow); }
[[gnu::weak]] void  operator delete[](void* ptr)                        noexcept { ::operator delete  (ptr); }
[[gnu::weak]] void  operator delete[](void* ptr, const std::nothrow_t&) noexcept { ::operator delete[](ptr); }
[[gnu::weak]] void  operator delete[](void* ptr, std::size_t)           noexcept { ::operator delete[](ptr); }
