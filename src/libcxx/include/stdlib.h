// -*- C++ -*-
#ifndef _EZCXX_STDLIB_H
#define _EZCXX_STDLIB_H

#include_next <stdlib.h>

#pragma clang system_header

namespace std {

inline constexpr long abs(long __x) { return __builtin_labs(__x); }

inline constexpr long long abs(long long __x) { return __builtin_llabs(__x); }

#ifdef __SIZEOF_INT48__
inline signed __int48 abs(signed __int48 __x) { return i48abs(__x); }
#endif // __SIZEOF_INT48__

inline constexpr float abs(float __x) { return __builtin_fabsf(__x); }

inline constexpr double abs(double __x) { return __builtin_fabs(__x); }

inline constexpr long double abs(long double __x) { return __builtin_fabsl(__x); }

inline constexpr ldiv_t div(long __x, long __y) { return ::ldiv(__x, __y); }

inline constexpr lldiv_t div(long long __x, long long __y) { return ::lldiv(__x, __y); }

#ifdef __SIZEOF_INT48__
inline i48div_t div(signed __int48 __x, signed __int48 __y) { return ::i48div(__x, __y); }
#endif // __SIZEOF_INT48__

using ::calloc;
using ::malloc;
using ::realloc;
using ::free;

using ::atof;
using ::atoi;
using ::atol;
using ::atoll;
using ::strtof;
using ::strtod;
using ::strtold;
using ::strtol;
using ::strtoll;
using ::strtoul;
using ::strtoull;

using ::srand;
using ::rand;

using ::bsearch;
using ::qsort;

using ::abort;
using ::atexit;
using ::on_exit;
using ::exit;
using ::at_quick_exit;
using ::quick_exit;
using ::_Exit;

using ::abs;
using ::labs;
using ::llabs;

using ::div;
using ::ldiv;
using ::lldiv;

#ifdef __SIZEOF_INT48__
using ::i48abs;
using ::i48div;
#endif // __SIZEOF_INT48__

} // namespace std

#endif // _EZCXX_STDLIB_H
