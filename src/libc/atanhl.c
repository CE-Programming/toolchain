#include <math.h>

long double atanhl(long double x)
{
    return .5l * logl((1 + x) / (1 - x));
}
