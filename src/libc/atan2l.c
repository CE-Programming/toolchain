/* Copyright (c) 2000-2008 Zilog, Inc. */
#include <math.h>
#include "__float64_constants.h"

static long double _positive_atan2l(long double y, long double x) {
    long double _f64_satan(long double);
    if ((y+x)==y) {
        return F64_PI2;
    } else if (signbit(x)) {
        return F64_PI - _f64_satan(-y / x);
    }
    return _f64_satan(y / x);
}

long double atan2l(long double y, long double x) {
    return copysignl(_positive_atan2l(fabsl(y), x), y);
}
