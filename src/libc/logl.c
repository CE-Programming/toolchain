/************************************************************************/
/*                                                                      */
/*                Copyright (C) 1999-2008 by Zilog, Inc.                */
/*                                                                      */
/************************************************************************/
/*
    log returns the natural logarithm of its floating
    point argument.

    The coefficients are #2705 from Hart & Cheney. (19.38D)

    It calls frexp.
*/

#include <errno.h>
#include <math.h>
#include "__float64_constants.h"

#define p0 -0.240139179559211e2L
#define p1  0.309572928215377e2L
#define p2 -0.963769093368687e1L
#define p3  0.421087371217980e0L
#define q0 -0.120069589779605e2L
#define q1  0.194809660700890e2L
#define q2 -0.891110902798312e1L

/**
 * @remarks Minimum relative precision of:
 * 2^-46.60 at +1.063981771e+00
 *
 * See the purple line for relative precision (lag warning):
 * https://www.desmos.com/calculator/gae4qofdtc
 */
long double logl(long double arg)
{
    long double x, z, zsq, temp;
    int expon;

    if (arg <= 0.0L) {
        errno = EDOM;
        return -HUGE_VALL;
    }
    x = frexpl(arg, & expon);
    if ( x < F64_INV_SQRT2 ) {
        x *= 2.0L;
        expon--;
    }

    z = (x-1.0L) / (x+1.0L);
    zsq = z*z;

    temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
    temp = temp / (((zsq + q2)*zsq + q1)*zsq + q0);
    temp = temp * z + expon * F64_LN2;
    return temp;
}
