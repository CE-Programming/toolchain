#include <math.h>

float roundf(float x)
{
    return copysignf(truncf(fabs(x) + .5f), x);
}

double round(double) __attribute__((alias("roundf")));
