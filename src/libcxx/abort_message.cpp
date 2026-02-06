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

#if 0
// Assembly version is used instead so we can avoid calling vsprintf
void __libcpp_verbose_abort(const char *format, ...) {
    va_list list;
    va_start(list, format);
    std::vsprintf(dbgerr, format, list);
    va_end(list);

    abort();
}
#endif

_LIBCPP_END_NAMESPACE_STD
