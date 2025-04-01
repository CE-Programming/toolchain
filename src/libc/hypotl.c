#include <math.h>
#include <stdint.h>

typedef union F64_pun {
	long double flt;
	uint64_t bin;
} F64_pun;

long double hypotl(long double arg_x, long double arg_y) {
	F64_pun x, y;
	x.flt = fabsl(arg_x);
	y.flt = fabsl(arg_y);
	if (x.bin < y.bin) {
		long double temp = x.flt;
		x.flt = y.flt;
		y.flt = temp;
	}
	// x >= y, or x is NaN
	if (isfinite(x.flt)) {
		int expon;
		// scale the arguments to prevent overflow/underflow
		x.flt = frexpl(x.flt, &expon);
		y.flt = ldexpl(y.flt, -expon);
		long double ret = sqrtl(x.flt * x.flt + y.flt * y.flt);
		return ldexpl(ret, expon);
	}
	if (isinf(y.flt)) {
		// return infinity, even if the other argument is NaN
		return y.flt;
	}
	// x is infinity/NaN
	return x.flt;
}
