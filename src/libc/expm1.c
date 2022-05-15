#include <math.h>

float expm1f(float x)
{
    return expf(x) - 1; // FIXME: accuracy
}

double expm1(double) __attribute__((alias("expm1f")));
