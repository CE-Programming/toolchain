#if PREFER_CE_LIBC

asm
(
    "\t.global _sinhf\n"
    "\t.type _sinhf, @function\n"
    "\t.equ _sinhf, 0x022130\n"
    "\t.global _sinh\n"
    "\t.type _sinh, @function\n"
    "\t.equ _sinh, _sinhf\n"
);

#else

#include <math.h>

#define p0 -0.630767364049772e+6f
#define p1 -0.899127202203951e+5f
#define p2 -0.289421135598956e+4f
#define p3 -0.263056321339750e+2f
#define q0 -0.630767364049772e+6f
#define q1  0.152151737879002e+5f
#define q2 -0.173678953558234e+3f

/**
 * @remarks Minimum ulp:
 * ulp of -3  at +0x1.eec25ap-9 with ideal expf (|x| < 21.0f)
 * ulp of -18 at +0x1.0a049cp+4 with current expf (|x| < 21.0f)
 */
float sinhf(float arg) {
    float temp, argsq, x;
    x = fabsf(arg);

    if (x < 0.5f) {
        argsq = x * x;
        temp = (((p3*argsq+p2)*argsq+p1)*argsq+p0) * x;
        temp /= (((argsq+q2)*argsq+q1)*argsq+q0);
    } else if (x < 88.5f) {
        temp = (expf(x) - expf(-x)) / 2.0f;
    } else {
        temp = expf(x - (float)M_LN2);
    }
    return copysignf(temp, arg);
}

double sinh(double) __attribute__((alias("sinhf")));

#endif
