#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -1  at +0x1.39a3fep-12 with ideal expf (|x| < 21.0f)
 * ulp of -18 at +0x1.0a049cp+4  with current expf (|x| < 21.0f)
 */
float _coshf_c(float x) {
    x = fabsf(x);
    if (x < 88.5f) {
        return (expf(x) + expf(-x)) / 2.0f;
    }
    return expf(x - (float)M_LN2);
}

double _cosh_c(double) __attribute__((alias("_coshf_c")));

