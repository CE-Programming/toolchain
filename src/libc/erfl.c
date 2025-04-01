#include <math.h>
#include "__float64_constants.h"

/**
 * @remarks Minimum ulp:
 * ulp of -513  at -0x1.35260d8034ac3p-10 with ideal erfcl
 * ulp of +6702 at -0x1.4ef5ac6f23690p-10 with current erfcl
 */
long double erfl(long double arg) {
	long double x = fabsl(arg);
	if (x < 0x1.0p-10L) {
		return F64_2_DIV_SQRTPI * (arg - arg * arg * arg * F64_1_DIV_3);
	}
	x = 1.0L - erfcl(x);
	return copysignl(x, arg);
}
