#include <math.h>

float logbf(float x)
{
    return floorf(log2f(x));
}

double logb(double) __attribute__((alias("logbf")));
