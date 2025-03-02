#include <math.h>

float asinhf(float x)
{
    return logf(x + sqrtf(x * x + 1));
}

double asinh(double) __attribute__((alias("asinhf")));
