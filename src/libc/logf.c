#if PREFER_OS_LIBC

asm
(
    "\t.global _logf\n"
    "\t.type _logf, @function\n"
    "\t.equ _logf, 0x0220E4\n"
    "\t.global _log\n"
    "\t.type _log, @function\n"
    "\t.equ _log, _logf\n"
);

#else

#include <errno.h>
#include <math.h>
#include "__float32_constants.h"

/**
 * @note These coefficients are for float64
 */
#define p0 -0.240139179559211e2f
#define p1  0.309572928215377e2f
#define p2 -0.963769093368687e1f
#define p3  0.421087371217980e0f
#define q0 -0.120069589779605e2f
#define q1  0.194809660700890e2f
#define q2 -0.891110902798312e1f

/**
 * @remarks Minimum ulp:
 * ulp of +4 at +0x1.8ef9aap-1
 *
 * See the purple line for relative precision (lag warning):
 * https://www.desmos.com/calculator/gae4qofdtc
 */
float logf(float arg)
{
    float x, z, zsq, temp;
    int expon;

    if (arg <= 0.0f) {
        errno = EDOM;
        return -HUGE_VALF;
    }
    x = frexpf(arg, & expon);
    if ( x < F32_INV_SQRT2 ) {
        x *= 2.0f;
        expon--;
    }

    z = (x-1.0f) / (x+1.0f);
    zsq = z*z;

    temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
    temp = temp / (((zsq + q2)*zsq + q1)*zsq + q0);
    temp = temp * z + expon * F32_LN2;
    return temp;
}

double log(double) __attribute__((alias("logf")));

#endif
