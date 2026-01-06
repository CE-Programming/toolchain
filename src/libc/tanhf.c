#if PREFER_OS_LIBC

asm
(
    "\t.global _tanhf\n"
    "\t.type _tanhf, @function\n"
    "\t.equ _tanhf, 0x022138\n"
    "\t.global _tanh\n"
    "\t.type _tanh, @function\n"
    "\t.equ _tanh, _tanhf\n"
);

#else

/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                             Zilog, Inc.                              */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/
/*
    tanh(arg) computes the hyperbolic tangent of its floating
    point argument.

    sinh and cosh are called except for large arguments, which
    would cause overflow improperly.
*/

#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -2 at +0x1.e0000cp-11 with ideal sinhf and coshf
 * ulp of -5 at +0x1.f921b4p-6  with current sinhf coshf and ideal expf
 * ulp of -7 at +0x1.0c2064p-1  with current sinhf coshf and expf
 */
float tanhf(float arg) {
    float x = fabsf(arg);

    // result rounds to 1.0f
    if(x > 10.0f) {
        x = 1.0f;
    } else {
        x = sinhf(x) / coshf(x);
    }

    return copysignf(x, arg);
}

double tanh(double) __attribute__((alias("tanhf")));

#endif
