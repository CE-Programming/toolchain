#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -257 at +0x1.ffe3f201d9f88p-808 assuming ideal logl expl
 */
long double cbrtl(long double x)
{
    if (x == 0.0L) {
        return x;
    }
    return copysignl(expl(logl(fabsl(x)) / 3.0L), x);
}
