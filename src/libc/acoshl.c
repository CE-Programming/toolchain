#include <math.h>
#include "__float64_constants.h"

/**
 * @remarks Minimum relative precision of:
 * 2^-42.37 at +1.000000358e+00 with ideal log1pl
 */
long double acoshl(long double x) {
	if (x < 0x1.0p+511L) {
		long double t = x - 1.0L;
		return log1pl(t + sqrtl(2.0L * t + t * t));
	}
	return logl(x) + F64_LN2;
}
