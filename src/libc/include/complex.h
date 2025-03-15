#ifndef _COMPLEX_H
#define _COMPLEX_H

#ifndef __FAST_MATH__
#warning "-ffast-math is required for complex multiplication and division to work properly at this time"
#endif

#ifndef __cplusplus
#define complex _Complex
#endif

#ifdef _Imaginary
#define imaginary _Imaginary
#endif

#ifndef I
# ifdef _Imaginary_I
#  define I _Imaginary_I
# else
#  define I _Complex_I
# endif
#endif

double _Complex CMPLX(double x, double y);
float _Complex CMPLXF(float x, float y);
long double _Complex CMPLXL(long double x, long double y);

#ifdef _Imaginary_I

#define CMPLX(x, y) ((double _Complex)((double)(x) + _Imaginary_I * (double)(y)))
#define CMPLXF(x, y) ((float _Complex)((float)(x) + _Imaginary_I * (float)(y)))
#define CMPLXL(x, y) ((long double _Complex)((long double)(x) + _Imaginary_I * (long double)(y)))

#endif /* _Imaginary_I */

double creal(double _Complex);
float crealf(float _Complex);
long double creall(long double _Complex);

double cimag(double _Complex);
float cimagf(float _Complex);
long double cimagl(long double _Complex);

double cabs(double _Complex);
float cabsf(float _Complex);
long double cabsl(long double _Complex);

double carg(double _Complex);
float cargf(float _Complex);
long double cargl(long double _Complex);

double _Complex conj(double _Complex);
float _Complex conjf(float _Complex);
long double _Complex conjl(long double _Complex);

double _Complex cproj(double _Complex);
float _Complex cprojf(float _Complex);
long double _Complex cprojl(long double _Complex);

double _Complex csqrt(double _Complex);
float _Complex csqrtf(float _Complex);
long double _Complex csqrtl(long double _Complex);

double _Complex cexp(double _Complex);
float _Complex cexpf(float _Complex);
long double _Complex cexpl(long double _Complex);

double _Complex clog(double _Complex);
float _Complex clogf(float _Complex);
long double _Complex clogl(long double _Complex);

double _Complex cpow(double _Complex, double _Complex);
float _Complex cpowf(float _Complex, float _Complex);
long double _Complex cpowl(long double _Complex, long double _Complex);

double _Complex csin(double _Complex);
float _Complex csinf(float _Complex);
long double _Complex csinl(long double _Complex);

double _Complex ccos(double _Complex);
float _Complex ccosf(float _Complex);
long double _Complex ccosl(long double _Complex);

double _Complex ctan(double _Complex);
float _Complex ctanf(float _Complex);
long double _Complex ctanl(long double _Complex);

double _Complex casin(double _Complex);
float _Complex casinf(float _Complex);
long double _Complex casinl(long double _Complex);

double _Complex cacos(double _Complex);
float _Complex cacosf(float _Complex);
long double _Complex cacosl(long double _Complex);

double _Complex catan(double _Complex);
float _Complex catanf(float _Complex);
long double _Complex catanl(long double _Complex);

double _Complex csinh(double _Complex);
float _Complex csinhf(float _Complex);
long double _Complex csinhl(long double _Complex);

double _Complex ccosh(double _Complex);
float _Complex ccoshf(float _Complex);
long double _Complex ccoshl(long double _Complex);

double _Complex ctanh(double _Complex);
float _Complex ctanhf(float _Complex);
long double _Complex ctanhl(long double _Complex);

double _Complex casinh(double _Complex);
float _Complex casinhf(float _Complex);
long double _Complex casinhl(long double _Complex);

double _Complex cacosh(double _Complex);
float _Complex cacoshf(float _Complex);
long double _Complex cacoshl(long double _Complex);

double _Complex catanh(double _Complex);
float _Complex catanhf(float _Complex);
long double _Complex catanhl(long double _Complex);

#endif /* _COMPLEX_H */
