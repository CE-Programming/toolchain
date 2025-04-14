#include <math.h>

long double remquol(long double x, long double y, int *quo)
{
    const long double quotient = roundevenl(x / y);
    *quo = quotient;
    return x - quotient * y; // FIXME: accuracy
}
