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
#define B0  1.0L
#define B1  (   -1.0L /    2.0L)
#define B2  (    1.0L /    6.0L)
#define B4  (   -1.0L /   30.0L)
#define B6  (    1.0L /   42.0L)
#define B8  (   -1.0L /   30.0L)
#define B10 (    5.0L /   66.0L)
#define B12 ( -691.0L / 2730.0L)
#define B14 (    7.0L /    6.0L)
#define B16 (-3617.0L /  510.0L)

#define ln_pi_div_2 0.91893853320467274178032973640562L

/**
 * @brief recycled from lgammaf
 * @remarks accuracy is not great, but the result appears to be +-1 ulp when
 * rounded to float in the range [0, 100], and +-32 ulp in the range [-10, 0]
 */
long double lgammal(long double x) { /* the natural logarithm of the Gamma function. */
    long double v, w;
    v = 1.0L;

    // this will overflow when x < 173.0L
    const int maximum_iter = 173 + N;
    for (int iter = 0; iter < maximum_iter; iter++) {
        if (!(x < (long double)N)) {
            break;
        }
        v *= x;
        x++;
    }
    w = 1.0L / (x * x);
    return ((((((((B16 / (16.0L * 15.0L))  * w + (B14 / (14.0L * 13.0L))) * w
                + (B12 / (12.0L * 11.0L))) * w + (B10 / (10.0L *  9.0L))) * w
                + (B8  / ( 8.0L *  7.0L))) * w + (B6  / ( 6.0L *  5.0L))) * w
                + (B4  / ( 4.0L *  3.0L))) * w + (B2  / ( 2.0L *  1.0L))) / x
                + ln_pi_div_2 - logl(fabsl(v)) - x + (x - 0.5L) * logl(fabsl(x));
}
