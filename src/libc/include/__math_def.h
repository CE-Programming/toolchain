#ifndef _MATH_DEF_H
#define _MATH_DEF_H

#include <cdefs.h>
#include <stdbool.h>

#define NAN          __builtin_nanf("")
#define INFINITY     __builtin_inff()

#define HUGE_VALF    __builtin_inff()
#define HUGE_VAL     __builtin_inf()
#define HUGE_VALL    __builtin_infl()

#define M_E           2.71828182845904523536     /* e              */
#define M_LOG2E       1.44269504088896340736     /* log2(e)        */
#define M_LOG10E      0.434294481903251827651    /* log10(e)       */
#define M_LN2         0.693147180559945309417    /* ln(2)          */
#define M_LN10        2.30258509299404568402     /* ln(10)         */
#define M_PI          3.14159265358979323846     /* pi             */
#define M_PI_2        1.57079632679489661923     /* pi/2           */
#define M_PI_4        0.785398163397448309616    /* pi/4           */
#define M_1_PI        0.318309886183790671538    /* 1/pi           */
#define M_2_PI        0.636619772367581343076    /* 2/pi           */
#define M_2_SQRTPI    1.12837916709551257390     /* 2/sqrt(pi)     */
#define M_SQRT2       1.41421356237309504880     /* sqrt(2)        */
#define M_SQRT1_2     0.707106781186547524401    /* 1/sqrt(2)      */

#define FP_ILOGB0     (~__INT_MAX__)
#define FP_ILOGBNAN     __INT_MAX__

#define FP_ZERO      0x0
#define FP_INFINITE  0x1
#define FP_SUBNORMAL 0x2
#define FP_NAN       0x3
#define FP_NORMAL    0x4

typedef float float_t;
typedef double double_t;

#ifdef __cplusplus
extern "C" {
#endif

int _fpclassifyf(float) __NOEXCEPT_CONST;
int _fpclassifyl(long double) __NOEXCEPT_CONST;

bool _issignalingf(float) __NOEXCEPT_CONST;
bool _isnanf(float) __NOEXCEPT_CONST;
bool _isinff(float) __NOEXCEPT_CONST;
bool _isfinitef(float) __NOEXCEPT_CONST;
bool _isnormalf(float) __NOEXCEPT_CONST;
bool _issubnormalf(float) __NOEXCEPT_CONST;
bool _iszerof(float) __NOEXCEPT_CONST;

bool _issignalingl(long double) __NOEXCEPT_CONST;
bool _isnanl(long double) __NOEXCEPT_CONST;
bool _isinfl(long double) __NOEXCEPT_CONST;
bool _isfinitel(long double) __NOEXCEPT_CONST;
bool _isnormall(long double) __NOEXCEPT_CONST;
bool _issubnormall(long double) __NOEXCEPT_CONST;
bool _iszerol(long double) __NOEXCEPT_CONST;

#if 0
/* disabled until builtin is optimized */
#define _signbitf(x) __builtin_signbit(x)
#define _signbitl(x) __builtin_signbit(x)
#else
bool _signbitf(float) __NOEXCEPT_CONST;
bool _signbitl(long double) __NOEXCEPT_CONST;
#endif

double      acos(double);
float       acosf(float);
long double acosl(long double);

double      acosh(double);
float       acoshf(float);
long double acoshl(long double);

double      asin(double);
float       asinf(float);
long double asinl(long double);

double      asinh(double);
float       asinhf(float);
long double asinhl(long double);

double      atan(double);
float       atanf(float);
long double atanl(long double);

double      atan2(double, double);
float       atan2f(float, float);
long double atan2l(long double, long double);

double      atanh(double);
float       atanhf(float);
long double atanhl(long double);

double      cbrt(double);
float       cbrtf(float);
long double cbrtl(long double);

double      ceil(double);
float       ceilf(float);
long double ceill(long double);

double      copysign(double, double);
float       copysignf(float, float);
long double copysignl(long double, long double);

double      cos(double);
float       cosf(float);
long double cosl(long double);

double      cospi(double);
float       cospif(float);
long double cospil(long double);

double      cosh(double);
float       coshf(float);
long double coshl(long double);

double      erf(double);
float       erff(float);
long double erfl(long double);

double      erfc(double);
float       erfcf(float);
long double erfcl(long double);

double      exp(double);
float       expf(float);
long double expl(long double);

double      exp2(double);
float       exp2f(float);
long double exp2l(long double);

double      expm1(double);
float       expm1f(float);
long double expm1l(long double);

#ifndef _ABS_FLOAT_DEFINED
#define _ABS_FLOAT_DEFINED
double      fabs(double);
float       fabsf(float);
long double fabsl(long double);
#endif /* _ABS_FLOAT_DEFINED */

double      fdim(double, double);
float       fdimf(float, float);
long double fdiml(long double, long double);

double      floor(double);
float       floorf(float);
long double floorl(long double);

double      fma(double, double, double);
float       fmaf(float, float, float);
long double fmal(long double, long double, long double);

double      fmax(double, double);
float       fmaxf(float, float);
long double fmaxl(long double, long double);

double      fmin(double, double);
float       fminf(float, float);
long double fminl(long double, long double);

double      fmod(double, double);
float       fmodf(float, float);
long double fmodl(long double, long double);

double      frexp(double, int *) __attribute__((nonnull(2)));
float       frexpf(float, int *) __attribute__((nonnull(2)));
long double frexpl(long double, int *) __attribute__((nonnull(2)));

double      hypot(double, double);
float       hypotf(float, float);
long double hypotl(long double, long double);

double      __hypot3(double, double, double);
float       __hypot3f(float, float, float);
long double __hypot3l(long double, long double, long double);

int         ilogb(double);
int         ilogbf(float);
int         ilogbl(long double);

double      ldexp(double, int);
float       ldexpf(float, int);
long double ldexpl(long double, int);

double      lgamma(double);
float       lgammaf(float);
long double lgammal(long double);

long long   llrint(double);
long long   llrintf(float);
long long   llrintl(long double);

long long   llround(double);
long long   llroundf(float);
long long   llroundl(long double);

double      log(double);
float       logf(float);
long double logl(long double);

double      log10(double);
float       log10f(float);
long double log10l(long double);

double      log1p(double);
float       log1pf(float);
long double log1pl(long double);

double      log2(double);
float       log2f(float);
long double log2l(long double);

double      logb(double);
float       logbf(float);
long double logbl(long double);

long        lrint(double);
long        lrintf(float);
long        lrintl(long double);

long        lround(double);
long        lroundf(float);
long        lroundl(long double);

double      modf(double, double *) __attribute__((nonnull(2)));
float       modff(float, float *) __attribute__((nonnull(2)));
long double modfl(long double, long double *) __attribute__((nonnull(2)));

double      nan(const char *);
float       nanf(const char *);
long double nanl(const char *);

double      nearbyint(double);
float       nearbyintf(float);
long double nearbyintl(long double);

double      nextafter(double, double);
float       nextafterf(float, float);
long double nextafterl(long double, long double);

double      nextdown(double);
float       nextdownf(float);
long double nextdownl(long double);

double      nexttoward(double, long double);
float       nexttowardf(float, long double);
long double nexttowardl(long double, long double);

double      nextup(double);
float       nextupf(float);
long double nextupl(long double);

double      pow(double, double);
float       powf(float, float);
long double powl(long double, long double);

double      remainder(double, double);
float       remainderf(float, float);
long double remainderl(long double, long double);

double      remquo(double, double, int *) __attribute__((nonnull(3)));
float       remquof(float, float, int *) __attribute__((nonnull(3)));
long double remquol(long double, long double, int *) __attribute__((nonnull(3)));

double      rint(double);
float       rintf(float);
long double rintl(long double);

double      round(double);
float       roundf(float);
long double roundl(long double);

double      roundeven(double);
float       roundevenf(float);
long double roundevenl(long double);

double      scalbln(double, long);
float       scalblnf(float, long);
long double scalblnl(long double, long);

double      scalbn(double, int);
float       scalbnf(float, int);
long double scalbnl(long double, int);

double      sin(double);
float       sinf(float);
long double sinl(long double);

double      sinpi(double);
float       sinpif(float);
long double sinpil(long double);

double      sinh(double);
float       sinhf(float);
long double sinhl(long double);

double      sqrt(double);
float       sqrtf(float);
long double sqrtl(long double);

double      tan(double);
float       tanf(float);
long double tanl(long double);

double      tanpi(double);
float       tanpif(float);
long double tanpil(long double);

double      tanh(double);
float       tanhf(float);
long double tanhl(long double);

double      tgamma(double);
float       tgammaf(float);
long double tgammal(long double);

double      trunc(double);
float       truncf(float);
long double truncl(long double);

#ifdef __cplusplus
}
#endif

#endif /* _MATH_DEF_H */
