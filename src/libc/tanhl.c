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
 * @remarks Approximate minimum ulp:
 * ulp of -3 at -0x1.eb3e727326400p+2 assuming ideal sinhl coshl
 * ulp of -5 at +0x1.02e0b35c71800p-2 assuming current sinhl coshl with ideal expl
 */
long double tanhl(long double arg) {
    long double x = fabsl(arg);

    // I think this rounds to 1.0 for float64 around 19.1
    if (x > 21.0L) {
        x = 1.0L;
    } else {
        x = sinhl(x) / coshl(x);
    }

    return copysignl(x, arg);
}
