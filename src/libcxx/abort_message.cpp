#undef NDEBUG
#include "abort_message.h"

#include <debug.h>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <ti/sprintf.h>
#include <__config>

void __terminate_message(const char *message) {
    boot_sprintf(dbgerr, "libezc++: %s\n", message);
    std::terminate();
}

void __abort_message(const char *message) {
    boot_sprintf(dbgerr, "libezc++: %s\n", message);
    abort();
}

_LIBCPP_BEGIN_NAMESPACE_STD

void __libcpp_verbose_abort(char const* format, ...) {
    va_list list;
    va_start(list, format);
    std::vsprintf(dbgerr, format, list);
    va_end(list);

    abort();
}

_LIBCPP_END_NAMESPACE_STD
