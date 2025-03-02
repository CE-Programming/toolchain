#include <math.h>

long double acoshl(long double x)
{
    return logl(x + sqrtl(x * x - 1));
}
