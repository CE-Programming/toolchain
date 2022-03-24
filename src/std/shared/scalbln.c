#include <math.h>

float scalblnf(float x, long exp)
{
    return x * exp2f(exp);
}

double scalbln(double, long) __attribute__((alias("scalblnf")));
