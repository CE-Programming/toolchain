#include <math.h>

float modff(float x, float *iptr)
{
    if (isfinite(x))
        return x - (*iptr = truncf(x));
    switch (isinf(*iptr = x)) {
        case -1: return -0.f;
        default: return x;
        case  1: return +0.f;
    }
}

double modf(double, double *) __attribute__((alias("modff")));
