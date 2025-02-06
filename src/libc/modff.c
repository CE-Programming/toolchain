#include <math.h>

float _modff_c(float x, float *iptr)
{
    if (isfinite(x))
        return x - (*iptr = truncf(x));
    switch (isinf(*iptr = x)) {
        case -1: return -0.f;
        default: return x;
        case  1: return +0.f;
    }
}

double _modf_c(double, double *) __attribute__((alias("_modff_c")));
