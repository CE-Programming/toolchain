#include <math.h>

float fdimf(float x, float y)
{
    return fmaxf(x - y, 0);
}

double fdim(double, double) __attribute__((alias("fdimf")));
