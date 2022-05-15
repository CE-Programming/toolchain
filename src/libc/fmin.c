#include <math.h>

float fminf(float x, float y)
{
    if (x != y) return x < y ? x : y;
    return !signbit(x) || isnan(x) ? y : x;
}

double fmin(double, double) __attribute__((alias("fminf")));
