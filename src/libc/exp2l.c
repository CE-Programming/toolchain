#include <math.h>
#include "__float64_constants.h"

long double exp2l(long double x)
{
    // this can be made much more accurately using frexp and ldexp
    return expl(x * F64_LN2);
}
