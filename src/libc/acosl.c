

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "__float64_constants.h"

/**
 * @remarks Minimum ulp:
 * ulp of -13337 at +0x1.ffffffe84b398p-1 assuming ideal atanl
 */
long double acosl(long double x) {
	if (x < 0.5L) {
		return F64_PI2 - asinl(x);
	}
	if (x <= 1.0L) {
		return atanl((sqrtl(1.0L - x) * sqrtl(1.0L + x)) / x);
	}
	errno = EDOM;
	return __builtin_nanl("");
}
