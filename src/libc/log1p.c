#include <math.h>

float log1pf(float x)
{
    return logf(1 + x);
}

double log1p(double) __attribute__((alias("log1pf")));
