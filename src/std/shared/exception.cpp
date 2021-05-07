#include <exception>

#include "abort_message.h"

#include <new>
#include <utility>

namespace std {

#define DEFINE_EXCEPTION(name)                                        \
    name::~name() noexcept {}                                         \
    const char* name::what() const noexcept { return "std::" #name; }
DEFINE_EXCEPTION(exception)
DEFINE_EXCEPTION(bad_exception)
DEFINE_EXCEPTION(bad_alloc)
#undef DEFINE_EXCEPTION

namespace {

[[noreturn]] void default_terminate_handler() {
    __abort_message("terminating");
}
[[clang::require_constant_initialization]] terminate_handler __terminate_handler = default_terminate_handler;

} // anonymous namespace

terminate_handler set_terminate(terminate_handler handler) noexcept {
    return exchange(__terminate_handler, handler ? handler : default_terminate_handler);
}
terminate_handler get_terminate() noexcept {
    return __terminate_handler;
}
void terminate() noexcept {
#if __has_feature(cxx_exceptions)
    try {
#endif
        set_terminate(nullptr)();
#if __has_feature(cxx_exceptions)
    } catch(...) {
        __abort_message("terminate_handler unexpectedly threw an exception");
    }
#endif
    __abort_message("terminate_handler unexpectedly returned");
}

} // namespace std
