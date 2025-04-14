#include <math.h>
#include "__float64_constants.h"

/**
 * @remarks Minimum ulp:
 * ulp of -1 at -0x1.f9134e7749c00p+0 with ideal expl (|x| < 709.0)
 * ulp of +496 at +0x1.62e4249341dc8p+9 with ideal expl (|x| >= 709.0)
 */
long double coshl(long double x) {
    x = fabsl(x);
    if (x < 709.0L) {
        return (expl(x) + expl(-x)) / 2.0L;
    }
    return expl(x - F64_LN2);
}
