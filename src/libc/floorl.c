#include <math.h>

long double floorl(long double x) {
    if (!signbit(x)) {
        return truncl(x);
    }
    if (!isfinite(x)) {
        return x;
    }
    long double frac = modfl(x, &x);
    if (!iszero(frac)) {
        x -= 1.0L;
    }
    return x;
}
