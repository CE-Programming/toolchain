#include <math.h>

float fmaf(float x, float y, float z)
{
    return x * y + z; // FIXME: accuracy
}

double fma(double, double, double) __attribute__((alias("fmaf")));
