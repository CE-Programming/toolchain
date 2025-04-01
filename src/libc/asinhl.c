#include <math.h>
#include "__float64_constants.h"

/**
 * @remarks Relative precision of:
 * 2^-42.41 at +9.768006857e-04 with ideal logl
 */
long double asinhl(long double arg) {
	long double x = fabsl(arg);
	if (x < 0x1.0p-10L) {
		x = x - (x * x * x) * F64_1_DIV_6;
	} else if (x < 0x1.0p+511L) {
		x = logl(x + sqrtl(x * x + 1.0L));
	} else {
		x = logl(x) + F64_LN2;
	}
	return copysignl(x, arg);
}
