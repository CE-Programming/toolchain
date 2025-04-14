/*
 * gamma.c  - public domain implementation of function tgamma(3m)
 * reference - Haruhiko Okumura: C-gengo niyoru saishin algorithm jiten
 *  (New Algorithm handbook in C language) (Gijyutsu hyouronsha, Tokyo, 1991) [in Japanese]
 *  http://oku.edu.mie-u.ac.jp/~okumura/algo/
*/

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "__float64_constants.h"

/** @brief recycled from tgammaf */
long double tgammal(long double x) { /* Gamma function */
    if (x == 0.0L) { /* Pole Error */
        errno = ERANGE;
        return signbit(x) ? -HUGE_VALL : HUGE_VALL;
    }
    if (x < 0.0L) {
        long double i, f, ret;
        f = modfl(-x, &i);
        if (f == 0.0L) { /* Domain Error */
            errno = EDOM;
            return __builtin_nanl("");
        }
        ret = F64_PI / (sinl(F64_PI * f) * expl(lgammal(1.0L - x)));
        if (((unsigned char)i & 0x1) == 0) {
            ret = -ret;
        }
        return ret;
    }
    return expl(lgammal(x));
}
