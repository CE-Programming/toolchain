#include <math.h>
#include "__float64_constants.h"

/**
 * @remarks Approximate minimum ulp:
 * ulp of +4097 at +0x1.0003239899b0ap-13 with ideal expl
 */
long double log1pl(long double x) {
	if (fabsl(x) < 0x1.2p-13L) {
		long double x_sqr = x * x;
		return (x_sqr * x) * F64_1_DIV_3 - 0.5L * (x_sqr) + x;
	}
	return logl(1.0L + x);
}
