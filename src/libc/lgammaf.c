/*
 * gamma.c  - public domain implementation of function tgamma(3m)
 * reference - Haruhiko Okumura: C-gengo niyoru saishin algorithm jiten
 *  (New Algorithm handbook in C language) (Gijyutsu hyouronsha, Tokyo, 1991) [in Japanese]
 *  http://oku.edu.mie-u.ac.jp/~okumura/algo/
*/

#include <math.h>
#include <errno.h>

#define N       8

#define B0  1.0               /* Bernoulli numbers */
#define B1  (-1.0 / 2.0)
#define B2  ( 1.0 / 6.0)
#define B4  (-1.0 / 30.0)
#define B6  ( 1.0 / 42.0)
#define B8  (-1.0 / 30.0)
#define B10 ( 5.0 / 66.0)
#define B12 (-691.0 / 2730.0)
#define B14 ( 7.0 / 6.0)
#define B16 (-3617.0 / 510.0)

float lgammaf(float x) { /* the natural logarithm of the Gamma function. */
    float v, w;
    v = 1.0;

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
    w = 1.0 / (x * x);
    return ((((((((B16 / (16.0 * 15.0))  * w + (B14 / (14.0 * 13.0))) * w
                + (B12 / (12.0 * 11.0))) * w + (B10 / (10.0 *  9.0))) * w
                + (B8  / ( 8.0 *  7.0))) * w + (B6  / ( 6.0 *  5.0))) * w
                + (B4  / ( 4.0 *  3.0))) * w + (B2  / ( 2.0 *  1.0))) / x
                + 0.5 * (float)M_LOG_2M_PI - logf(v) - x + (x - 0.5) * logf(x);
}

double lgamma(double) __attribute__((alias("lgammaf")));
