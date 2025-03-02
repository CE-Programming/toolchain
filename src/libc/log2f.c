#include <math.h>

float log2f(float x)
{
    return logf(x) * (float)(1 / M_LN2);
}

double log2(double) __attribute__((alias("log2f")));
