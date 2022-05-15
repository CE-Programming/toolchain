#include <math.h>

float fmaxf(float x, float y)
{
    if (x != y) return x < y ? y : x;
    return signbit(x) || isnan(x) ? y : x;
}

double fmax(double, double) __attribute__((alias("fmaxf")));
