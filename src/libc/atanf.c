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
#include "__float32_constants.h"

/**
 * @note These coefficients are for float64
 */
#define p4 0.161536412982230e2f
#define p3 0.268425481955040e3f
#define p2 0.115302935154049e4f
#define p1 0.178040631643320e4f
#define p0 0.896785974036639e3f
#define q4 0.589569705084446e2f
#define q3 0.536265374031215e3f
#define q2 0.166678381488163e4f
#define q1 0.207933497444541e4f
#define q0 0.896785974036639e3f

/**
 * atan makes its argument positive and
 * calls the inner routine satan.
 *
 * @remarks Minimum ulp:
 * ulp of +4 at +0x1.a85846p-2
 */
float _atanf_c(float arg) {
    float _f32_satan(float);
    return copysignf(_f32_satan(fabsf(arg)), arg);
}

double _atan_c(double) __attribute__((alias("_atanf_c")));

/**
 * atan2 discovers what quadrant the angle
 * is in and calls atan.
 */

/**
 * xatan evaluates a series valid in the
 * range [-0.414...,+0.414...].
 */
static float _f32_xatan(float arg) {
    float argsq;
    float value;

    argsq = arg*arg;
    value = ((((p4*argsq + p3)*argsq + p2)*argsq + p1)*argsq + p0);
    value = value/(((((argsq + q4)*argsq + q3)*argsq + q2)*argsq + q1)*argsq + q0);
    return (value*arg);
}

/**
 * satan reduces its argument (known to be positive)
 * to the range [0,0.414...] and calls xatan.
 */
float _f32_satan(float arg) {
    if (arg < F32_SQRT2_MINUS_1) {
        return (_f32_xatan(arg));
    } else if (arg > F32_SQRT2_PLUS_1) {
        if (arg > 0x1.0p+25f) {
            /* rounds to pi/2 */
            return F32_PI2;
        }
        return (F32_PI2 - _f32_xatan(1.0f/arg));
    } else {
        return (F32_PI4 + _f32_xatan((arg-1.0f)/(arg+1.0f)));
    }
}
