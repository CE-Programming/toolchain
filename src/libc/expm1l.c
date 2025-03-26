#include <math.h>
#include "__float64_constants.h"

/**
 * @remarks Approximate minimum ulp:
 * ulp of -4098 at +0x1.3683c27b9c856p-13 with ideal expl
 */
long double expm1l(long double x) {
    if (fabsl(x) < 0x1.0p-13L) {
        long double x_sqr = x * x;
        return (x_sqr * x) * F64_1_DIV_3 + 0.5L * (x_sqr) + x;
    }
    return expl(x) - 1.0L;
}
