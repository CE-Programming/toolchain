/* Copyright (c) 2000-2008 Zilog, Inc. */

/**
 * floating-point arctangent
 *
 * atan returns the value of the arctangent of its
 * argument in the range [-pi/2,pi/2].
 *
 * atan2 returns the arctangent of arg1/arg2
 * in the range [-pi,pi].
 *
 * there are no error returns.
 *
 * coefficients are #5077 from Hart & Cheney. (19.56D)
 */
#include <math.h>
#include "__float64_constants.h"

#define p4 0.161536412982230e2L
#define p3 0.268425481955040e3L
#define p2 0.115302935154049e4L
#define p1 0.178040631643320e4L
#define p0 0.896785974036639e3L
#define q4 0.589569705084446e2L
#define q3 0.536265374031215e3L
#define q2 0.166678381488163e4L
#define q1 0.207933497444541e4L
#define q0 0.896785974036639e3L

/**
 * atan makes its argument positive and
 * calls the inner routine satan.
 *
 * @remarks Minimum relative precision of:
 * 2^-46.95 at +2.438776493e+00
 */
long double atanl(long double arg) {
    long double _f64_satan(long double);
    return copysignl(_f64_satan(fabsl(arg)), arg);
}

/**
 * atan2 discovers what quadrant the angle
 * is in and calls atan.
 */

/**
 * xatan evaluates a series valid in the
 * range [-0.414...,+0.414...].
 */

static long double _f64_xatan(long double arg) {
    long double argsq;
    long double value;

    argsq = arg*arg;
    value = ((((p4*argsq + p3)*argsq + p2)*argsq + p1)*argsq + p0);
    value = value/(((((argsq + q4)*argsq + q3)*argsq + q2)*argsq + q1)*argsq + q0);
    return (value*arg);
}

/**
 * satan reduces its argument (known to be positive)
 * to the range [0,0.414...] and calls xatan.
 */

long double _f64_satan(long double arg) {
    if (arg < F64_SQRT2_MINUS_1) {
        return _f64_xatan(arg);
    } else if (arg > F64_SQRT2_PLUS_1) {
        if (arg > 0x1.0p+54L) {
            /* rounds to pi/2 */
            return F64_PI2;
        }
        return (F64_PI2 - _f64_xatan(1.0L / arg));
    } else {
        return (F64_PI4 + _f64_xatan((arg - 1.0L) / (arg + 1.0L)));
    }
}
