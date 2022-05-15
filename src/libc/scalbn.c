#include <math.h>

float scalbnf(float x, int exp)
{
    return x * exp2f(exp);
}

double scalbn(double, int) __attribute__((alias("scalbnf")));
