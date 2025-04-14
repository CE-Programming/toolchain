#include <math.h>
#include "__float64_constants.h"

long double log2l(long double x)
{
    // this can be made much more accurately using frexp and ldexp
    return logl(x) * F64_LOG2E;
}
