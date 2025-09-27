#include <errno.h>
#include <fenv.h>
#include <math.h>

long double logbl(long double x) {
    if (isfinite(x)) {
        if (iszero(x)) {
            errno = EDOM;
            feraiseexcept(FE_DIVBYZERO);
            return -HUGE_VALL;
        }
        return (long double)ilogbl(x);
    }
    // infinity and NaN
    return fabsl(x);
}
