#ifndef _TGMATH_H
#define _TGMATH_H

#ifdef __cplusplus

#include <cmath>

#else /* __cplusplus */

#include <math.h>

#define __tgmath_promote(x) _Generic((x), \
    float: ((float)0.f), \
    default: ((double)0.), \
    long double: ((long double)0.L) \
)

/* single argument */

#define acos(x) _Generic(__tgmath_promote(x), \
    long double: acosl, \
    default: acos, \
    float: acosf \
)(x)

#define acosh(x) _Generic(__tgmath_promote(x), \
    long double: acoshl, \
    default: acosh, \
    float: acoshf \
)(x)

#define asin(x) _Generic(__tgmath_promote(x), \
    long double: asinl, \
    default: asin, \
    float: asinf \
)(x)

#define asinh(x) _Generic(__tgmath_promote(x), \
    long double: asinhl, \
    default: asinh, \
    float: asinhf \
)(x)

#define atan(x) _Generic(__tgmath_promote(x), \
    long double: atanl, \
    default: atan, \
    float: atanf \
)(x)

#define atanh(x) _Generic(__tgmath_promote(x), \
    long double: atanhl, \
    default: atanh, \
    float: atanhf \
)(x)

#define cbrt(x) _Generic(__tgmath_promote(x), \
    long double: cbrtl, \
    default: cbrt, \
    float: cbrtf \
)(x)

#define ceil(x) _Generic(__tgmath_promote(x), \
    long double: ceill, \
    default: ceil, \
    float: ceilf \
)(x)

#define cos(x) _Generic(__tgmath_promote(x), \
    long double: cosl, \
    default: cos, \
    float: cosf \
)(x)

#define cospi(x) _Generic(__tgmath_promote(x), \
    long double: cospil, \
    default: cospi, \
    float: cospif \
)(x)

#define cosh(x) _Generic(__tgmath_promote(x), \
    long double: coshl, \
    default: cosh, \
    float: coshf \
)(x)

#define erf(x) _Generic(__tgmath_promote(x), \
    long double: erfl, \
    default: erf, \
    float: erff \
)(x)

#define erfc(x) _Generic(__tgmath_promote(x), \
    long double: erfcl, \
    default: erfc, \
    float: erfcf \
)(x)

#define exp(x) _Generic(__tgmath_promote(x), \
    long double: expl, \
    default: exp, \
    float: expf \
)(x)

#define exp2(x) _Generic(__tgmath_promote(x), \
    long double: exp2l, \
    default: exp2, \
    float: exp2f \
)(x)

#define expm1(x) _Generic(__tgmath_promote(x), \
    long double: expm1l, \
    default: expm1, \
    float: expm1f \
)(x)

#define fabs(x) _Generic(__tgmath_promote(x), \
    long double: fabsl, \
    default: fabs, \
    float: fabsf \
)(x)

#define floor(x) _Generic(__tgmath_promote(x), \
    long double: floorl, \
    default: floor, \
    float: floorf \
)(x)

#define ilogb(x) _Generic(__tgmath_promote(x), \
    long double: ilogbl, \
    default: ilogb, \
    float: ilogbf \
)(x)

#define lgamma(x) _Generic(__tgmath_promote(x), \
    long double: lgammal, \
    default: lgamma, \
    float: lgammaf \
)(x)

#define llrint(x) _Generic(__tgmath_promote(x), \
    long double: llrintl, \
    default: llrint, \
    float: llrintf \
)(x)

#define llround(x) _Generic(__tgmath_promote(x), \
    long double: llroundl, \
    default: llround, \
    float: llroundf \
)(x)

#define log(x) _Generic(__tgmath_promote(x), \
    long double: logl, \
    default: log, \
    float: logf \
)(x)

#define log10(x) _Generic(__tgmath_promote(x), \
    long double: log10l, \
    default: log10, \
    float: log10f \
)(x)

#define log1p(x) _Generic(__tgmath_promote(x), \
    long double: log1pl, \
    default: log1p, \
    float: log1pf \
)(x)

#define log2(x) _Generic(__tgmath_promote(x), \
    long double: log2l, \
    default: log2, \
    float: log2f \
)(x)

#define logb(x) _Generic(__tgmath_promote(x), \
    long double: logbl, \
    default: logb, \
    float: logbf \
)(x)

#define lrint(x) _Generic(__tgmath_promote(x), \
    long double: lrintl, \
    default: lrint, \
    float: lrintf \
)(x)

#define lround(x) _Generic(__tgmath_promote(x), \
    long double: lroundl, \
    default: lround, \
    float: lroundf \
)(x)

#define nearbyint(x) _Generic(__tgmath_promote(x), \
    long double: nearbyintl, \
    default: nearbyint, \
    float: nearbyintf \
)(x)

#define nextdown(x) _Generic(__tgmath_promote(x), \
    long double: nextdownl, \
    default: nextdown, \
    float: nextdownf \
)(x)

#define nextup(x) _Generic(__tgmath_promote(x), \
    long double: nextupl, \
    default: nextup, \
    float: nextupf \
)(x)

#define rint(x) _Generic(__tgmath_promote(x), \
    long double: rintl, \
    default: rint, \
    float: rintf \
)(x)

#define round(x) _Generic(__tgmath_promote(x), \
    long double: roundl, \
    default: round, \
    float: roundf \
)(x)

#define roundeven(x) _Generic(__tgmath_promote(x), \
    long double: roundevenl, \
    default: roundeven, \
    float: roundevenf \
)(x)

#define sin(x) _Generic(__tgmath_promote(x), \
    long double: sinl, \
    default: sin, \
    float: sinf \
)(x)

#define sinpi(x) _Generic(__tgmath_promote(x), \
    long double: sinpil, \
    default: sinpi, \
    float: sinpif \
)(x)

#define sinh(x) _Generic(__tgmath_promote(x), \
    long double: sinhl, \
    default: sinh, \
    float: sinhf \
)(x)

#define sqrt(x) _Generic(__tgmath_promote(x), \
    long double: sqrtl, \
    default: sqrt, \
    float: sqrtf \
)(x)

#define tan(x) _Generic(__tgmath_promote(x), \
    long double: tanl, \
    default: tan, \
    float: tanf \
)(x)

#define tanpi(x) _Generic(__tgmath_promote(x), \
    long double: tanpil, \
    default: tanpi, \
    float: tanpif \
)(x)

#define tanh(x) _Generic(__tgmath_promote(x), \
    long double: tanhl, \
    default: tanh, \
    float: tanhf \
)(x)

#define tgamma(x) _Generic(__tgmath_promote(x), \
    long double: tgammal, \
    default: tgamma, \
    float: tgammaf \
)(x)

#define trunc(x) _Generic(__tgmath_promote(x), \
    long double: truncl, \
    default: trunc, \
    float: truncf \
)(x)

/* two identical arguments */

#define atan2(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: atan2l, \
    default: atan2, \
    float: atan2f \
)((x), (y))

#define copysign(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: copysignl, \
    default: copysign, \
    float: copysignf \
)((x), (y))

#define fdim(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: fdiml, \
    default: fdim, \
    float: fdimf \
)((x), (y))

#define fmax(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: fmaxl, \
    default: fmax, \
    float: fmaxf \
)((x), (y))

#define fmin(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: fminl, \
    default: fmin, \
    float: fminf \
)((x), (y))

#define fmod(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: fmodl, \
    default: fmod, \
    float: fmodf \
)((x), (y))

#define nextafter(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: nextafterl, \
    default: nextafter, \
    float: nextafterf \
)((x), (y))

#define pow(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: powl, \
    default: pow, \
    float: powf \
)((x), (y))

#define remainder(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: remainderl, \
    default: remainder, \
    float: remainderf \
)((x), (y))

/* multiple arguments */

#define fma(x, y, z) _Generic(__tgmath_promote(x) + __tgmath_promote(y) + __tgmath_promote(z), \
    long double: fmal, \
    default: fma, \
    float: fmaf \
)((x), (y), (z))

#define frexp(x, y) _Generic(__tgmath_promote(x), \
    long double: frexpl, \
    default: frexp, \
    float: frexpf \
)((x), (y))

#define ldexp(x, y) _Generic(__tgmath_promote(x), \
    long double: ldexpl, \
    default: ldexp, \
    float: ldexpf \
)((x), (y))

#define nexttoward(x, y) _Generic(__tgmath_promote(x), \
    long double: nexttowardl, \
    default: nexttoward, \
    float: nexttowardf \
)((x), (y))

#define remquo(x, y, z) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: remquol, \
    default: remquo, \
    float: remquof \
)((x), (y), (z))

#define scalbln(x, y) _Generic(__tgmath_promote(x), \
    long double: scalblnl, \
    default: scalbln, \
    float: scalblnf \
)((x), (y))

#define scalbn(x, y) _Generic(__tgmath_promote(x), \
    long double: scalbnl, \
    default: scalbn, \
    float: scalbnf \
)((x), (y))

/* hypot */

#define __tgmath_hypot2(x, y) _Generic(__tgmath_promote(x) + __tgmath_promote(y), \
    long double: hypotl, \
    default: hypot, \
    float: hypotf \
)((x), (y))

#define __tgmath_hypot3(x, y, z) _Generic(__tgmath_promote(x) + __tgmath_promote(y) + __tgmath_promote(z), \
    long double: __hypot3l, \
    default: __hypot3, \
    float: __hypot3f \
)((x), (y), (z))

#define __tgmath_hypot_count(_1,_2,_3,count,...)count
#define __tgmath_JOIN2(X,Y)X##Y
#define __tgmath_CONCAT(X,Y)__tgmath_JOIN2(X,Y)
#define hypot(...)__tgmath_CONCAT(__tgmath_hypot,__tgmath_hypot_count(__VA_ARGS__,3,2,))(__VA_ARGS__)

#endif /* __cplusplus */

#endif /* _TGMATH_H */
