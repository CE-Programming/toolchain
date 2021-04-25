// -*- C++ -*-
#ifndef _EZCXX_CXXABI_H
#define _EZCXX_CXXABI_H

#include <stdlib.h>

#pragma GCC system_header

#ifdef __cplusplus

namespace __cxxabiv1 {
extern "C" {

// 3.2.6 Pure Virtual Function API
[[noreturn]] void __cxa_pure_virtual();

// 3.2.7 Deleted Virtual Function API
[[noreturn]] void __cxa_deleted_virtual();

} // extern "C"
} // namespace __cxxabiv1

#endif // __cplusplus

#endif // _EZCXX_CXXABI_H
