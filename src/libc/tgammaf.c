/*
 * gamma.c  - public domain implementation of function tgamma(3m)
 * reference - Haruhiko Okumura: C-gengo niyoru saishin algorithm jiten
 *  (New Algorithm handbook in C language) (Gijyutsu hyouronsha, Tokyo, 1991) [in Japanese]
 *  http://oku.edu.mie-u.ac.jp/~okumura/algo/
*/

#include <errno.h>
#include <math.h>
#include <stdbool.h>

/**
 * @remarks Minimum relative precision of:
 * 2^-15.34 at +3.226818848e+01 with ideal sinf expf and lgammaf (x > 0.0f)
 * 2^-17    at +2.940585591e-39 with ideal sinf expf and lgammaf (x > 0.0f && x < 10.0f)
 * 2^-17.91 at +9.224035263e+00 with ideal sinf expf and lgammaf (x > 0.1f && x < 10.0f)
 */
float tgammaf(float x) { /* Gamma function */
    if (x == 0.0f) { /* Pole Error */
        errno = ERANGE;
        return signbit(x) ? -HUGE_VALF : HUGE_VALF;
    }
    if (x < 0.0f) {
    static float zero = 0.0f;
        float i, f, ret;
        f = modff(-x, &i);
        if (f == 0.0f) { /* Domain Error */
            errno = EDOM;
            return zero/zero; /* probably better to return NAN here */
        }
        ret = (float)M_PI / (sinf((float)M_PI * f) * expf(lgammaf(1.0f - x)));
        if (((unsigned int)i & 0x1) == 0) {
            ret = -ret;
        }
        return ret;
    }
    return expf(lgammaf(x));
}

double tgamma(double) __attribute__((alias("tgammaf")));
