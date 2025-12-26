#if PREFER_CE_LIBC

asm
(
    "\t.global _atan2f\n"
    "\t.type _atan2f, @function\n"
    "\t.equ _atan2f, 0x02210C\n"
    "\t.global _atan2\n"
    "\t.type _atan2, @function\n"
    "\t.equ _atan2, _atan2f\n"
);

#else

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

float atan2f(float y, float x) {
    return copysignf(_positive_atan2f(fabsf(y), x), y);
}

double atan2(double, double) __attribute__((alias("atan2f")));

#endif
