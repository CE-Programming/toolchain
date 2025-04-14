#include <math.h>

float remainderf(float x, float y)
{
    return x - roundevenf(x / y) * y;
}

double remainder(double, double) __attribute__((alias("remainderf")));
