#ifndef _MATH_H
#define _MATH_H

#ifdef __cplusplus

#include <cmath>

#else /* __cplusplus */

#include <__math_def.h>

#define __math_promote(x) _Generic((x), \
    float: ((float)0.f), \
    default: ((double)0.), \
    long double: ((long double)0.L) \
)

#define signbit(x) ((int)_Generic(__math_promote(x), \
    long double: _signbitl, \
    default: _signbitf, \
    float: _signbitf \
)(x))

#define issignaling(x) ((int)_Generic(__math_promote(x), \
    long double: _issignalingl, \
    default: _issignalingf, \
    float: _issignalingf \
)(x))

#define isnan(x) ((int)_Generic(__math_promote(x), \
    long double: _isnanl, \
    default: _isnanf, \
    float: _isnanf \
)(x))


#define isinf(x) ((int)_Generic(__math_promote(x), \
    long double: _isinfl, \
    default: _isinff, \
    float: _isinff \
)(x))

#define isfinite(x) ((int)_Generic(__math_promote(x), \
    long double: _isfinitel, \
    default: _isfinitef, \
    float: _isfinitef \
)(x))

#define isnormal(x) ((int)_Generic(__math_promote(x), \
    long double: _isnormall, \
    default: _isnormalf, \
    float: _isnormalf \
)(x))

#define issubnormal(x) ((int)_Generic(__math_promote(x), \
    long double: _issubnormall, \
    default: _issubnormalf, \
    float: _issubnormalf \
)(x))

#define iszero(x) ((int)_Generic(__math_promote(x), \
    long double: _iszerol, \
    default: _iszerof, \
    float: _iszerof \
)(x))

#define fpclassify(x) ((int)_Generic(__math_promote(x), \
    long double: _fpclassifyl, \
    default: _fpclassifyf, \
    float: _fpclassifyf \
)(x))

#define isgreater(x, y)      __builtin_isgreater(x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal(x, y)
#define isless(x, y)         __builtin_isless(x, y)
#define islessequal(x, y)    __builtin_islessequal(x, y)
#define islessgreater(x, y)  __builtin_islessgreater(x, y)
#define isunordered(x, y)    __builtin_isunordered(x, y)

#endif /* __cplusplus */

#endif /* _MATH_H */
