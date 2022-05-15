#include <math.h>

float atanhf(float x)
{
    return .5f * logf((1 + x) / (1 - x));
}

double atanh(double) __attribute__((alias("atanhf")));

long double atanhl(long double x)
{
    return .5l * logl((1 + x) / (1 - x));
}
