/* Copyright (c) 2000-2008 Zilog, Inc. */

/**
 * asin(arg) return the arcsin of arg.
 * arctan is called after appropriate range reduction.
 */

#include    <errno.h>
#include    <math.h>

#define pio2  1.57079632679490f

float _asinf_c(float arg)
{
    float sign, temp;
    sign = copysignf(1.0f, arg);
    arg = fabsf(arg);

    if(arg > 1.0f) {
        errno = EDOM;
        return 0.0f;
    }

    temp = sqrtf(1.0f - arg*arg);
    if(arg > 0.7f) {
        temp = pio2 - atanf(temp/arg);
    } else {
        temp = atanf(arg/temp);
    }

    return copysignf(temp, sign);
}

double _asin_c(double) __attribute__((alias("_asinf_c")));
