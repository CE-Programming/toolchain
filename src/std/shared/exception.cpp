#include <exception>
#include <new>

namespace std {

#define DEFINE_EXCEPTION(name)                                        \
    name::~name() noexcept {}                                         \
    const char* name::what() const noexcept { return "std::" #name; }
DEFINE_EXCEPTION(exception)
DEFINE_EXCEPTION(bad_exception)
DEFINE_EXCEPTION(bad_alloc)
#undef DEFINE_EXCEPTION

} // namespace std
