#if PREFER_CE_LIBC

asm
(
    "\t.global _coshf\n"
    "\t.type _coshf, @function\n"
    "\t.equ _coshf, 0x022134\n"
    "\t.global _cosh\n"
    "\t.type _cosh, @function\n"
    "\t.equ _cosh, _coshf\n"
);

#else

#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -1  at +0x1.39a3fep-12 with ideal expf (|x| < 21.0f)
 * ulp of -18 at +0x1.0a049cp+4  with current expf (|x| < 21.0f)
 */
float coshf(float x) {
    x = fabsf(x);
    if (x < 88.5f) {
        return (expf(x) + expf(-x)) / 2.0f;
    }
    return expf(x - (float)M_LN2);
}

double cosh(double) __attribute__((alias("coshf")));

#endif
