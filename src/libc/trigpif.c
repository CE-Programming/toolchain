#include <math.h>
#include "__float32_constants.h"

static float reduce_f32(float x) {
    // x is (-2.0, +2.0)
    return (x - 2.0f * truncf(x * 0.5f)) * F32_PI;
}

float sinpif(float x) {
    return sinf(reduce_f32(x));
}

float cospif(float x) {
    return cosf(reduce_f32(x));
}

float tanpif(float x) {
    return tanf(reduce_f32(x));
}

double sinpi(double) __attribute__((alias("sinpif")));
double cospi(double) __attribute__((alias("cospif")));
double tanpi(double) __attribute__((alias("tanpif")));
