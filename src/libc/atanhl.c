#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -2	at +0x1.cf33c905a6324p-4 with ideal log1pl
 * ulp of +4098 at +0x1.ffff1c95280b8p-15 with current log1pl and ideal logl
 * ulp of +4135 at -0x1.f319bfec310c4p-14 with current log1pl and logl
 */
long double atanhl(long double arg) {
	long double x = fabsl(arg);
	x = 0.5L * log1pl((2.0L * x) / (1.0L - x));
	return copysignl(x, arg);
}
