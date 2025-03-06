/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                             Zilog, Inc.                              */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/
/*
    sinh(arg) returns the hyperbolic sine of its floating-
    point argument.

    The exponential function is called for arguments
    greater in magnitude than 0.5.

    A series is used for arguments smaller in magnitude than 0.5.
    The coefficients are #2029 from Hart & Cheney. (20.36D)

    cosh(arg) is computed from the exponential function for
    all arguments.
*/

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
float _sinhf_c(float arg) {
    float temp, argsq, x;
    x = fabsf(arg);

    if (x > 21.0f) {
        temp = expf(x) / 2.0f;
    } else if (x > 0.5f) {
        temp = (expf(x) - expf(-x)) / 2.0f;
    } else {
        argsq = x * x;
        temp = (((p3*argsq+p2)*argsq+p1)*argsq+p0) * x;
        temp /= (((argsq+q2)*argsq+q1)*argsq+q0);
    }
    return copysignf(temp, arg);
}

double _sinh_c(double, double *) __attribute__((alias("_sinhf_c")));
