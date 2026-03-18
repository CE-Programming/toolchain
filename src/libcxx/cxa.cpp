#include <stdint.h>
#include "abort_message.h"

// https://itanium-cxx-abi.github.io/cxx-abi/abi.html#dso-dtor-runtime-api

// __int64_t
typedef int64_t __guard;

extern "C" {
[[gnu::cold]] int __cxa_guard_acquire(__guard *);
[[gnu::cold]] void __cxa_guard_release(__guard *);
[[noreturn, gnu::cold]] void __cxa_guard_abort(__guard *);
}

int __cxa_guard_acquire(__guard *guard_object) {
    unsigned char const *flag = (unsigned char const *)guard_object;
    if (*flag == 0) {
        // initialization not yet complete
        return 1;
    }
    // otherwise
    return 0;
}

void __cxa_guard_release(__guard *guard_object) {
    unsigned char *flag = (unsigned char *)guard_object;
    // set to a non-zero value
    *flag = 1;
}

void __cxa_guard_abort([[maybe_unused]] __guard *guard_object) {
    std::__abort_message("__cxa_guard_abort");
}
