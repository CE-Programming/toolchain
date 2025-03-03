/*
 * gamma.c  - public domain implementation of function tgamma(3m)
 * reference - Haruhiko Okumura: C-gengo niyoru saishin algorithm jiten
 *  (New Algorithm handbook in C language) (Gijyutsu hyouronsha, Tokyo, 1991) [in Japanese]
 *  http://oku.edu.mie-u.ac.jp/~okumura/algo/
*/

#include <math.h>
#include <errno.h>

float tgammaf(float x) { /* Gamma function */
    if (x == 0.0) { /* Pole Error */
        errno = ERANGE;
        return signbit(x) ? -HUGE_VALF : HUGE_VALF;
    }
    if (x < 0) {
        int sign;
    static float zero = 0.0;
        float i, f;
        f = modff(-x, &i);
        if (f == 0.0) { /* Domain Error */
            errno = EDOM;
            return zero/zero; /* probably better to return NAN here */
        }
        sign = (fmodf(i, 2.0) != 0.0) ? 1 : -1;
        return (sign * M_PI) / (sinf(M_PI * f) * expf(lgammaf(1 - x)));
    }
    return expf(lgammaf(x));
}

double tgamma(double) __attribute__((alias("tgammaf")));
