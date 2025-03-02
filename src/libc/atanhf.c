#include <math.h>

float atanhf(float x)
{
    return .5f * logf((1 + x) / (1 - x));
}

double atanh(double) __attribute__((alias("atanhf")));
