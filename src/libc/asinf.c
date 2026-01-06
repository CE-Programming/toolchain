#if PREFER_OS_LIBC

asm
(
    "\t.global _asinf\n"
    "\t.type _asinf, @function\n"
    "\t.equ _asinf, 0x022104\n"
    "\t.global _asin\n"
    "\t.type _asin, @function\n"
    "\t.equ _asin, _asinf\n"
);

#else

/* Copyright (c) 2000-2008 Zilog, Inc. */

/**
 * asin(arg) return the arcsin of arg.
 * arctan is called after appropriate range reduction.
 */

#include <errno.h>
#include <math.h>
#include <stdbool.h>

/**
 * @remarks Minimum ulp:
 * ulp of +8 at +0x1.ffe956p-1
 */
float asinf(float arg) {
    bool arg_sign;
    float temp;
    arg_sign = signbit(arg);
    arg = fabsf(arg);

    if(arg > 1.0f) {
        errno = EDOM;
        return 0.0f;
    }

    temp = sqrtf(1.0f - arg*arg);
    if(arg > 0.7f) {
        temp = (float)M_PI_2 - atanf(temp/arg);
    } else {
        temp = atanf(arg/temp);
    }
    if (arg_sign) {
        temp = -temp;
    }
    return temp;
}

double asin(double) __attribute__((alias("asinf")));

#endif
