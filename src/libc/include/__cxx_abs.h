#ifndef _CXX_ABS_H
#define _CXX_ABS_H

#include <__stdlib_abs.h>
#include <__math_abs.h>

#pragma clang system_header

// https://cplusplus.github.io/LWG/issue2192

namespace std {
using ::abs;

inline constexpr long abs(long __x) { return labs(__x); }

#ifdef __SIZEOF_INT48__
inline signed __int48 abs(signed __int48 __x) { return i48abs(__x); }
#endif // __SIZEOF_INT48__

inline constexpr long long abs(long long __x) { return llabs(__x); }

inline constexpr float abs(float __x) { return fabsf(__x); }

inline constexpr double abs(double __x) { return fabs(__x); }

inline constexpr long double abs(long double __x) { return fabsl(__x); }

} // namespace std

#endif /* _CXX_ABS_H */
