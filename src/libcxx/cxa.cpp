#include "abort_message.h"

// https://itanium-cxx-abi.github.io/cxx-abi/abi.html#dso-dtor-runtime-api

extern "C" {
void __cxa_pure_virtual();
void __cxa_deleted_virtual();
int __cxa_guard_acquire(long long *);
int __cxa_guard_release(long long *);
int __cxa_guard_abort(long long *);
}

__attribute__((__cold__))
void __cxa_pure_virtual() {
    __abort_message("__cxa_pure_virtual");
}

__attribute__((__cold__))
void __cxa_deleted_virtual() {
    __abort_message("__cxa_deleted_virtual");
}

__attribute__((__cold__))
int __cxa_guard_acquire(long long *guard_object) {
    unsigned char const *ptr = (unsigned char const *)guard_object;
    if (*ptr == 0) {
        // initialization not yet complete
        return 1;
    }
    // otherwise
    return 0;
}

__attribute__((__cold__))
int __cxa_guard_release(long long *guard_object) {
    unsigned char *ptr = (unsigned char *)guard_object;
    // set to a non-zero value
    *ptr = 1;
    return 0;
}

__attribute__((__cold__))
int __cxa_guard_abort(__attribute__((__unused__)) long long *guard_object) {
    __abort_message("__cxa_guard_abort");
}
