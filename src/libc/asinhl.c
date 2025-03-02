#include <math.h>

long double asinhl(long double x)
{
    return logl(x + sqrtl(x * x + 1));
}
