#include <math.h>
#include "__float64_constants.h"

long double log10l(long double x)
{
    return logl(x) * F64_LOG10E;
}
