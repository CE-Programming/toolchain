#include <math.h>

float cbrtf(float x)
{
    return copysignf(powf(fabsf(x), 1.f/3.f), x);
}

double cbrt(double) __attribute__((alias("cbrtf")));
