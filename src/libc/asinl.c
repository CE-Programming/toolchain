/* Copyright (c) 2000-2008 Zilog, Inc. */

/**
 * asin(arg) return the arcsin of arg.
 * arctan is called after appropriate range reduction.
 */

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "__float64_constants.h"

/**
 * @remarks Minimum ulp:
 * ulp of -805 at -0x1.ffffffc97db1bp-1 assuming ideal atanl
 */
long double asinl(long double arg) {
    bool arg_sign;
    long double temp;
    arg_sign = signbit(arg);
    arg = fabsl(arg);

    if (arg > 1.0L) {
        errno = EDOM;
        return 0.0L;
    }

    temp = sqrtl(1.0L - arg * arg);
    if (arg > 0.7L) {
        temp = F64_PI2 - atanl(temp / arg);
    } else {
        temp = atanl(arg / temp);
    }
    if (arg_sign) {
        temp = -temp;
    }
    return temp;
}
