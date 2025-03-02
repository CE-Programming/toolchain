#include <fenv.h>
#include <math.h>

float rintf(float x)
{
    float result = nearbyintf(x);
    if (result != x) feraiseexcept(FE_INEXACT);
    return result;
}

double rint(double) __attribute__((alias("rintf")));
