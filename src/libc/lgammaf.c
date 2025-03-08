/*
 * gamma.c  - public domain implementation of function tgamma(3m)
 * reference - Haruhiko Okumura: C-gengo niyoru saishin algorithm jiten
 *  (New Algorithm handbook in C language) (Gijyutsu hyouronsha, Tokyo, 1991) [in Japanese]
 *  http://oku.edu.mie-u.ac.jp/~okumura/algo/
*/

#include <math.h>
#include <errno.h>

#define N       8

/* Bernoulli numbers */
#define B0  1.0f
#define B1  (   -1.0f /    2.0f)
#define B2  (    1.0f /    6.0f)
#define B4  (   -1.0f /   30.0f)
#define B6  (    1.0f /   42.0f)
#define B8  (   -1.0f /   30.0f)
#define B10 (    5.0f /   66.0f)
#define B12 ( -691.0f / 2730.0f)
#define B14 (    7.0f /    6.0f)
#define B16 (-3617.0f /  510.0f)

#define ln_pi_div_2 0.91893853320467274178032973640562f

/**
 * @remarks Minimum relative precision of:
 * 2^-16.97 at +3.205794811e+00 with ideal logf (x > 3.0f)
 * 2^-16.71 at +2.940585591e-39 with ideal logf (x > 0.0f && x < 0.5f)
 * 2^-13.68 at +1.591955781e+00 with ideal logf (x > 1.25f && x < 1.75f)
 * @note input values 0.5f - 3.0f have very low precision
 */
float lgammaf(float x) { /* the natural logarithm of the Gamma function. */
    float v, w;
    v = 1.0f;

    /**
     * This loop will take forever to terminate if `x < -100.0f`, so we have a
     * maximum iteration count to ensure that the loop will terminate in a
     * reasonable amount of time. `v` should overflow when `x < -33.0f`
     */
    const int maximum_iter = 36 + N;
    for (int iter = 0; iter < maximum_iter; iter++) {
        if (x < (float)N) {
            break;
        }
        v *= x;
        x++;
    }
    w = 1.0f / (x * x);
    return ((((((((B16 / (16.0f * 15.0f))  * w + (B14 / (14.0f * 13.0f))) * w
                + (B12 / (12.0f * 11.0f))) * w + (B10 / (10.0f *  9.0f))) * w
                + (B8  / ( 8.0f *  7.0f))) * w + (B6  / ( 6.0f *  5.0f))) * w
                + (B4  / ( 4.0f *  3.0f))) * w + (B2  / ( 2.0f *  1.0f))) / x
                + ln_pi_div_2 - logf(v) - x + (x - 0.5f) * logf(x);
}

double lgamma(double) __attribute__((alias("lgammaf")));
