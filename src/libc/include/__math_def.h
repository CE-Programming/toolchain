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

#ifdef DEBUG_FOOBAR

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

double      frexp(double, int *) ;
float       frexpf(float, int *) ;
long double frexpl(long double, int *) ;

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

double      modf(double, double *) ;
float       modff(float, float *) ;
long double modfl(long double, long double *) ;

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

double      remquo(double, double, int *) ;
float       remquof(float, float, int *) ;
long double remquol(long double, long double, int *) ;

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

#else

static inline double      acos(double x) { return __builtin_acos(x); }
static inline float       acosf(float x) { return __builtin_acosf(x); }
static inline long double acosl(long double x) { return __builtin_acosl(x); }

static inline double      acosh(double x) { return __builtin_acosh(x); }
static inline float       acoshf(float x) { return __builtin_acoshf(x); }
static inline long double acoshl(long double x) { return __builtin_acoshl(x); }

static inline double      asin(double x) { return __builtin_asin(x); }
static inline float       asinf(float x) { return __builtin_asinf(x); }
static inline long double asinl(long double x) { return __builtin_asinl(x); }

static inline double      asinh(double x) { return __builtin_asinh(x); }
static inline float       asinhf(float x) { return __builtin_asinhf(x); }
static inline long double asinhl(long double x) { return __builtin_asinhl(x); }

static inline double      atan(double x) { return __builtin_atan(x); }
static inline float       atanf(float x) { return __builtin_atanf(x); }
static inline long double atanl(long double x) { return __builtin_atanl(x); }

static inline double      atan2(double y, double x) { return __builtin_atan2(y, x); }
static inline float       atan2f(float y, float x) { return __builtin_atan2f(y, x); }
static inline long double atan2l(long double y, long double x) { return __builtin_atan2l(y, x); }

static inline double      atanh(double x) { return __builtin_atanh(x); }
static inline float       atanhf(float x) { return __builtin_atanhf(x); }
static inline long double atanhl(long double x) { return __builtin_atanhl(x); }

static inline double      cbrt(double x) { return __builtin_cbrt(x); }
static inline float       cbrtf(float x) { return __builtin_cbrtf(x); }
static inline long double cbrtl(long double x) { return __builtin_cbrtl(x); }

static inline double      ceil(double x) { return __builtin_ceil(x); }
static inline float       ceilf(float x) { return __builtin_ceilf(x); }
static inline long double ceill(long double x) { return __builtin_ceill(x); }

static inline double      copysign(double x, double y) { return __builtin_copysign(x, y); }
static inline float       copysignf(float x, float y) { return __builtin_copysignf(x, y); }
static inline long double copysignl(long double x, long double y) { return __builtin_copysignl(x, y); }

static inline double      cos(double x) { return __builtin_cos(x); }
static inline float       cosf(float x) { return __builtin_cosf(x); }
static inline long double cosl(long double x) { return __builtin_cosl(x); }

double      cospi(double);
float       cospif(float);
long double cospil(long double);

static inline double      cosh(double x) { return __builtin_cosh(x); }
static inline float       coshf(float x) { return __builtin_coshf(x); }
static inline long double coshl(long double x) { return __builtin_coshl(x); }

static inline double      erf(double x) { return __builtin_erf(x); }
static inline float       erff(float x) { return __builtin_erff(x); }
static inline long double erfl(long double x) { return __builtin_erfl(x); }

static inline double      erfc(double x) { return __builtin_erfc(x); }
static inline float       erfcf(float x) { return __builtin_erfcf(x); }
static inline long double erfcl(long double x) { return __builtin_erfcl(x); }

static inline double      exp(double x) { return __builtin_exp(x); }
static inline float       expf(float x) { return __builtin_expf(x); }
static inline long double expl(long double x) { return __builtin_expl(x); }

static inline double      exp2(double x) { return __builtin_exp2(x); }
static inline float       exp2f(float x) { return __builtin_exp2f(x); }
static inline long double exp2l(long double x) { return __builtin_exp2l(x); }

static inline double      expm1(double x) { return __builtin_expm1(x); }
static inline float       expm1f(float x) { return __builtin_expm1f(x); }
static inline long double expm1l(long double x) { return __builtin_expm1l(x); }

#ifndef _ABS_FLOAT_DEFINED
#define _ABS_FLOAT_DEFINED
double      fabs(double x);
float       fabsf(float x);
long double fabsl(long double x);
#endif /* _ABS_FLOAT_DEFINED */

static inline double      fdim(double x, double y) { return __builtin_fdim(x, y); }
static inline float       fdimf(float x, float y) { return __builtin_fdimf(x, y); }
static inline long double fdiml(long double x, long double y) { return __builtin_fdiml(x, y); }

static inline double      floor(double x) { return __builtin_floor(x); }
static inline float       floorf(float x) { return __builtin_floorf(x); }
static inline long double floorl(long double x) { return __builtin_floorl(x); }

static inline double      fma(double x, double y, double z) { return __builtin_fma(x, y, z); }
static inline float       fmaf(float x, float y, float z) { return __builtin_fmaf(x, y, z); }
static inline long double fmal(long double x, long double y, long double z) { return __builtin_fmal(x, y, z); }

static inline double      fmax(double x, double y) { return __builtin_fmax(x, y); }
static inline float       fmaxf(float x, float y) { return __builtin_fmaxf(x, y); }
static inline long double fmaxl(long double x, long double y) { return __builtin_fmaxl(x, y); }

static inline double      fmin(double x, double y) { return __builtin_fmin(x, y); }
static inline float       fminf(float x, float y) { return __builtin_fminf(x, y); }
static inline long double fminl(long double x, long double y) { return __builtin_fminl(x, y); }

static inline double      fmod(double x, double y) { return __builtin_fmod(x, y); }
static inline float       fmodf(float x, float y) { return __builtin_fmodf(x, y); }
static inline long double fmodl(long double x, long double y) { return __builtin_fmodl(x, y); }

static inline double      frexp(double x, int *e)  { return __builtin_frexp(x, e); }
static inline float       frexpf(float x, int *e)  { return __builtin_frexpf(x, e); }
static inline long double frexpl(long double x, int *e)  { return __builtin_frexpl(x, e); }

static inline double      hypot(double x, double y) { return __builtin_hypot(x, y); }
static inline float       hypotf(float x, float y) { return __builtin_hypotf(x, y); }
static inline long double hypotl(long double x, long double y) { return __builtin_hypotl(x, y); }

double      __hypot3(double, double, double);
float       __hypot3f(float, float, float);
long double __hypot3l(long double, long double, long double);

static inline int         ilogb(double x) { return __builtin_ilogb(x); }
static inline int         ilogbf(float x) { return __builtin_ilogbf(x); }
static inline int         ilogbl(long double x) { return __builtin_ilogbl(x); }

static inline double      ldexp(double x, int e) { return __builtin_ldexp(x, e); }
static inline float       ldexpf(float x, int e) { return __builtin_ldexpf(x, e); }
static inline long double ldexpl(long double x, int e) { return __builtin_ldexpl(x, e); }

static inline double      lgamma(double x) { return __builtin_lgamma(x); }
static inline float       lgammaf(float x) { return __builtin_lgammaf(x); }
static inline long double lgammal(long double x) { return __builtin_lgammal(x); }

static inline long long   llrint(double x) { return __builtin_llrint(x); }
static inline long long   llrintf(float x) { return __builtin_llrintf(x); }
static inline long long   llrintl(long double x) { return __builtin_llrintl(x); }

static inline long long   llround(double x) { return __builtin_llround(x); }
static inline long long   llroundf(float x) { return __builtin_llroundf(x); }
static inline long long   llroundl(long double x) { return __builtin_llroundl(x); }

static inline double      log(double x) { return __builtin_log(x); }
static inline float       logf(float x) { return __builtin_logf(x); }
static inline long double logl(long double x) { return __builtin_logl(x); }

static inline double      log10(double x) { return __builtin_log10(x); }
static inline float       log10f(float x) { return __builtin_log10f(x); }
static inline long double log10l(long double x) { return __builtin_log10l(x); }

static inline double      log1p(double x) { return __builtin_log1p(x); }
static inline float       log1pf(float x) { return __builtin_log1pf(x); }
static inline long double log1pl(long double x) { return __builtin_log1pl(x); }

static inline double      log2(double x) { return __builtin_log2(x); }
static inline float       log2f(float x) { return __builtin_log2f(x); }
static inline long double log2l(long double x) { return __builtin_log2l(x); }

static inline double      logb(double x) { return __builtin_logb(x); }
static inline float       logbf(float x) { return __builtin_logbf(x); }
static inline long double logbl(long double x) { return __builtin_logbl(x); }

static inline long        lrint(double x) { return __builtin_lrint(x); }
static inline long        lrintf(float x) { return __builtin_lrintf(x); }
static inline long        lrintl(long double x) { return __builtin_lrintl(x); }

static inline long        lround(double x) { return __builtin_lround(x); }
static inline long        lroundf(float x) { return __builtin_lroundf(x); }
static inline long        lroundl(long double x) { return __builtin_lroundl(x); }

static inline double      modf(double x, double *ip)  { return __builtin_modf(x, ip); }
static inline float       modff(float x, float *ip)  { return __builtin_modff(x, ip); }
static inline long double modfl(long double x, long double *ip)  { return __builtin_modfl(x, ip); }

static inline double      nan(const char *s) { return __builtin_nan(s); }
static inline float       nanf(const char *s) { return __builtin_nanf(s); }
static inline long double nanl(const char *s) { return __builtin_nanl(s); }

static inline double      nearbyint(double x) { return __builtin_nearbyint(x); }
static inline float       nearbyintf(float x) { return __builtin_nearbyintf(x); }
static inline long double nearbyintl(long double x) { return __builtin_nearbyintl(x); }

static inline double      nextafter(double x, double y) { return __builtin_nextafter(x, y); }
static inline float       nextafterf(float x, float y) { return __builtin_nextafterf(x, y); }
static inline long double nextafterl(long double x, long double y) { return __builtin_nextafterl(x, y); }

double      nextdown(double);
float       nextdownf(float);
long double nextdownl(long double);

static inline double      nexttoward(double x, long double y) { return __builtin_nexttoward(x, y); }
static inline float       nexttowardf(float x, long double y) { return __builtin_nexttowardf(x, y); }
static inline long double nexttowardl(long double x, long double y) { return __builtin_nexttowardl(x, y); }

double      nextup(double);
float       nextupf(float);
long double nextupl(long double);

static inline double      pow(double x, double y) { return __builtin_pow(x, y); }
static inline float       powf(float x, float y) { return __builtin_powf(x, y); }
static inline long double powl(long double x, long double y) { return __builtin_powl(x, y); }

static inline double      remainder(double x, double y) { return __builtin_remainder(x, y); }
static inline float       remainderf(float x, float y) { return __builtin_remainderf(x, y); }
static inline long double remainderl(long double x, long double y) { return __builtin_remainderl(x, y); }

static inline double      remquo(double x, double y, int *q)  { return __builtin_remquo(x, y, q); }
static inline float       remquof(float x, float y, int *q)  { return __builtin_remquof(x, y, q); }
static inline long double remquol(long double x, long double y, int *q)  { return __builtin_remquol(x, y, q); }

static inline double      rint(double x) { return __builtin_rint(x); }
static inline float       rintf(float x) { return __builtin_rintf(x); }
static inline long double rintl(long double x) { return __builtin_rintl(x); }

static inline double      round(double x) { return __builtin_round(x); }
static inline float       roundf(float x) { return __builtin_roundf(x); }
static inline long double roundl(long double x) { return __builtin_roundl(x); }

double      roundeven(double);
float       roundevenf(float);
long double roundevenl(long double);

static inline double      scalbln(double x, long n) { return __builtin_scalbln(x, n); }
static inline float       scalblnf(float x, long n) { return __builtin_scalblnf(x, n); }
static inline long double scalblnl(long double x, long n) { return __builtin_scalblnl(x, n); }

static inline double      scalbn(double x, int n) { return __builtin_scalbn(x, n); }
static inline float       scalbnf(float x, int n) { return __builtin_scalbnf(x, n); }
static inline long double scalbnl(long double x, int n) { return __builtin_scalbnl(x, n); }

static inline double      sin(double x) { return __builtin_sin(x); }
static inline float       sinf(float x) { return __builtin_sinf(x); }
static inline long double sinl(long double x) { return __builtin_sinl(x); }

double      sinpi(double);
float       sinpif(float);
long double sinpil(long double);

static inline double      sinh(double x) { return __builtin_sinh(x); }
static inline float       sinhf(float x) { return __builtin_sinhf(x); }
static inline long double sinhl(long double x) { return __builtin_sinhl(x); }

static inline double      sqrt(double x) { return __builtin_sqrt(x); }
static inline float       sqrtf(float x) { return __builtin_sqrtf(x); }
static inline long double sqrtl(long double x) { return __builtin_sqrtl(x); }

static inline double      tan(double x) { return __builtin_tan(x); }
static inline float       tanf(float x) { return __builtin_tanf(x); }
static inline long double tanl(long double x) { return __builtin_tanl(x); }

double      tanpi(double);
float       tanpif(float);
long double tanpil(long double);

static inline double      tanh(double x) { return __builtin_tanh(x); }
static inline float       tanhf(float x) { return __builtin_tanhf(x); }
static inline long double tanhl(long double x) { return __builtin_tanhl(x); }

static inline double      tgamma(double x) { return __builtin_tgamma(x); }
static inline float       tgammaf(float x) { return __builtin_tgammaf(x); }
static inline long double tgammal(long double x) { return __builtin_tgammal(x); }

static inline double      trunc(double x) { return __builtin_trunc(x); }
static inline float       truncf(float x) { return __builtin_truncf(x); }
static inline long double truncl(long double x) { return __builtin_truncl(x); }

#endif

#ifdef __cplusplus
}
#endif

#endif /* _MATH_DEF_H */
