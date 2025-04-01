#include <math.h>

float fdimf(float x, float y) {
	/**
	 * returns `x - y` when `x > y` or if one of the arguments is NaN.
	 * Otherwise returns positive zero.
	 */
	return islessequal(x, y) ? 0.0f : (x - y);
}

double fdim(double, double) __attribute__((alias("fdimf")));

long double fdiml(long double x, long double y) {
	/**
	 * returns `x - y` when `x > y` or if one of the arguments is NaN.
	 * Otherwise returns positive zero.
	 */
	return islessequal(x, y) ? 0.0L : (x - y);
}
