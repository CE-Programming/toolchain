#include <math.h>

float fmodf(float x, float y)
{
    return x - truncf(x / y) * y;
}

double fmod(double, double) __attribute__((alias("fmodf")));
