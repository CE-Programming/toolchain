/* Copyright (c) 2000-2008 Zilog, Inc. */
#include <math.h>
#include "__float32_constants.h"

static float _positive_atan2f(float y, float x) {
    float _f32_satan(float);
    if ((y+x)==y) {
        return F32_PI2;
    } else if (signbit(x)) {
        return F32_PI - _f32_satan(-y / x);
    }
    return _f32_satan(y / x);
}

float _atan2f_c(float y, float x) {
    return copysignf(_positive_atan2f(fabsf(y), x), y);
}

double _atan2_c(double, double) __attribute__((alias("_atan2f_c")));
