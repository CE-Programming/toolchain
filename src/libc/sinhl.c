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
#include "__float64_constants.h"

#define p0 -0.630767364049772e+6L
#define p1 -0.899127202203951e+5L
#define p2 -0.289421135598956e+4L
#define p3 -0.263056321339750e+2L
#define q0 -0.630767364049772e+6L
#define q1  0.152151737879002e+5L
#define q2 -0.173678953558234e+3L

/**
 * @remarks Approximate minimum ulp:
 * ulp of -3 at +0x1.d535220f91000p-2 with ideal expl (|x| < 709.0)
 * ulp of +496 at +0x1.62e428917b3fcp+9 with ideal expl (|x| >= 709.0)
 */
long double sinhl(long double arg) {
    long double temp, argsq, x;
    x = fabsl(arg);
	if (x < 0.5L) {
        argsq = x * x;
        temp = (((p3*argsq+p2)*argsq+p1)*argsq+p0) * x;
        temp /= (((argsq+q2)*argsq+q1)*argsq+q0);
	} else if (x < 709.0L) {
		temp = (expl(x) - expl(-x)) / 2.0L;
	} else {
		temp = expl(x - F64_LN2);
	}
    return copysignl(temp, arg);
}
