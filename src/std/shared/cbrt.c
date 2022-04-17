#include <math.h>

float cbrtf(float x)
{
    return powf(x, 1/3.f);
}

double cbrt(double) __attribute__((alias("cbrtf")));
