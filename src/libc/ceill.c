#include <math.h>

#ifdef ceill
#undef ceill
#endif

long double ceill(long double x) {
	if (signbit(x)) {
		return truncl(x);
	}
	if (!isfinite(x)) {
		return x;
	}
	long double frac = modfl(x, &x);
	if (!iszero(frac)) {
		x += 1.0L;
	}
	return x;
}

long double _debug_ceill(long double) __attribute__((alias("ceill")));
