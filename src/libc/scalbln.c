#include <math.h>

float scalblnf(float x, long expon)
{
    return scalbnf(x, (int)expon);
}

double scalbln(double, long) __attribute__((alias("scalblnf")));

long double scalblnl(long double x, long expon)
{
    return scalbnl(x, (int)expon);
}
