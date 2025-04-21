#ifndef _MATH_H
#define _MATH_H

#ifdef __cplusplus

#include <cmath>

#else /* __cplusplus */

#include <__math_def.h>

static inline __attribute__((__always_inline__))
bool __signbitf(float __x) {
    if (__builtin_constant_p(__x)) {
        return (__builtin_copysign(1.0f, __x) < 0.0f);
    }
    return _signbitf(__x);
}
static inline __attribute__((__always_inline__))
bool __signbitl(long double __x) {
    if (__builtin_constant_p(__x)) {
        return (__builtin_copysign(1.0L, __x) < 0.0L);
    }
    return _signbitl(__x);
}

static inline __attribute__((__always_inline__))
bool __issignalingf(float __x) {
    return _issignalingf(__x);
}
static inline __attribute__((__always_inline__))
bool __issignalingl(long double __x) {
    return _issignalingl(__x);
}

static inline __attribute__((__always_inline__))
bool __isnanf(float __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isnan(__x);
    }
    return _isnanf(__x);
}
static inline __attribute__((__always_inline__))
bool __isnanl(long double __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isnan(__x);
    }
    return _isnanl(__x);
}

static inline __attribute__((__always_inline__))
bool __isinff(float __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isinf(__x);
    }
    return _isinff(__x);
}
static inline __attribute__((__always_inline__))
bool __isinfl(long double __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isinf(__x);
    }
    return _isinfl(__x);
}

static inline __attribute__((__always_inline__))
bool __isfinitef(float __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isfinite(__x);
    }
    return _isfinitef(__x);
}
static inline __attribute__((__always_inline__))
bool __isfinitel(long double __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isfinite(__x);
    }
    return _isfinitel(__x);
}

static inline __attribute__((__always_inline__))
bool __isnormalf(float __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isnormal(__x);
    }
    return _isnormalf(__x);
}
static inline __attribute__((__always_inline__))
bool __isnormall(long double __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_isnormal(__x);
    }
    return _isnormall(__x);
}

static inline __attribute__((__always_inline__))
bool __issubnormalf(float __x) {
    if (__builtin_constant_p(__x)) {
        return (FP_SUBNORMAL == __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, __x));
    }
    return _issubnormalf(__x);
}
static inline __attribute__((__always_inline__))
bool __issubnormall(long double __x) {
    if (__builtin_constant_p(__x)) {
        return (FP_SUBNORMAL == __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, __x));
    }
    return _issubnormall(__x);
}

static inline __attribute__((__always_inline__))
bool __iszerof(float __x) {
    if (__builtin_constant_p(__x)) {
        return (__x == 0.0f);
    }
    return _iszerof(__x);
}
static inline __attribute__((__always_inline__))
bool __iszerol(long double __x) {
    if (__builtin_constant_p(__x)) {
        return (__x == 0.0L);
    }
    return _iszerol(__x);
}

static inline __attribute__((__always_inline__))
int __fpclassifyf(float __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, __x);
    } else {
        return _fpclassifyf(__x);
    }
}
static inline __attribute__((__always_inline__))
int __fpclassifyl(long double __x) {
    if (__builtin_constant_p(__x)) {
        return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, __x);
    } else {
        return _fpclassifyl(__x);
    }
}

#define __math_promote(x) _Generic((x), \
    float: ((float)0.f), \
    default: ((double)0.), \
    long double: ((long double)0.L) \
)

#define signbit(x) ((int)_Generic(__math_promote(x), \
    long double: __signbitl, \
    default: __signbitf, \
    float: __signbitf \
)(x))

#define issignaling(x) ((int)_Generic(__math_promote(x), \
    long double: __issignalingl, \
    default: __issignalingf, \
    float: __issignalingf \
)(x))

#define isnan(x) ((int)_Generic(__math_promote(x), \
    long double: __isnanl, \
    default: __isnanf, \
    float: __isnanf \
)(x))

#define isinf(x) ((int)_Generic(__math_promote(x), \
    long double: __isinfl, \
    default: __isinff, \
    float: __isinff \
)(x))

#define isfinite(x) ((int)_Generic(__math_promote(x), \
    long double: __isfinitel, \
    default: __isfinitef, \
    float: __isfinitef \
)(x))

#define isnormal(x) ((int)_Generic(__math_promote(x), \
    long double: __isnormall, \
    default: __isnormalf, \
    float: __isnormalf \
)(x))

#define issubnormal(x) ((int)_Generic(__math_promote(x), \
    long double: __issubnormall, \
    default: __issubnormalf, \
    float: __issubnormalf \
)(x))

#define iszero(x) ((int)_Generic(__math_promote(x), \
    long double: __iszerol, \
    default: __iszerof, \
    float: __iszerof \
)(x))

#define fpclassify(x) ((int)_Generic(__math_promote(x), \
    long double: __fpclassifyl, \
    default: __fpclassifyf, \
    float: __fpclassifyf \
)(x))

#define isgreater(x, y)      __builtin_isgreater(x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal(x, y)
#define isless(x, y)         __builtin_isless(x, y)
#define islessequal(x, y)    __builtin_islessequal(x, y)
#define islessgreater(x, y)  __builtin_islessgreater(x, y)
#define isunordered(x, y)    __builtin_isunordered(x, y)

#endif /* __cplusplus */

#endif /* _MATH_H */
