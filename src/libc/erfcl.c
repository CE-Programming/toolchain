#include <math.h>

/**
 * Algorithm from:
 * https://en.wikipedia.org/wiki/Error_function#Approximation_with_elementary_functions
 *
 * @remarks Minimum ulp:
 * ulp of -516 at +2.373300261e+01 with ideal expl
 */
long double _erfcl_c(long double arg) {
    long double x, x_sqr;
    long double t0, t1, t2, t3, t4, t5;
    long double ret;
    
    x = fabsl(arg);
    x_sqr = x * x;
    t0 = 0.56418958354775629L / (x + 2.06955023132914151L);
    t1 =
        (x_sqr + 2.71078540045147805L * x +  5.80755613130301624L) /
        (x_sqr + 3.47954057099518960L * x + 12.06166887286239555L);
    t2 =
        (x_sqr + 3.47469513777439592L * x + 12.07402036406381411L) /
        (x_sqr + 3.72068443960225092L * x +  8.44319781003968454L);
    t3 =
        (x_sqr + 4.00561509202259545L * x +  9.30596659485887898L) /
        (x_sqr + 3.90225704029924078L * x +  6.36161630953880464L);
    t4 =
        (x_sqr + 5.16722705817812584L * x +  9.12661617673673262L) /
        (x_sqr + 4.03296893109262491L * x +  5.13578530585681539L);
    t5 =
        (x_sqr + 5.95908795446633271L * x +  9.19435612886969243L) /
        (x_sqr + 4.11240942957450885L * x +  4.48640329523408675L);
    ret = ((((t0 * t1) * t2) * t3) * t4) * t5;
    ret *= expl(-x_sqr);
    if (signbit(arg)) {
        ret = 2.0L - ret;
    }
    return ret;
}
