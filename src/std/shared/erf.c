#include <math.h>

float erff(float x)
{
    return 1 - erfcf(x);
}

double erf(double) __attribute__((alias("erff")));

long double erfl(long double x)
{
    return 1 - erfcl(x);
}
