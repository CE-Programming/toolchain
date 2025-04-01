#include <math.h>
#include "__float64_constants.h"

static long double reduce_f64(long double x) {
	// x is (-2.0, +2.0)
	return (x - 2.0L * truncl(x * 0.5L)) * F64_PI;
}

long double sinpil(long double x) {
	return sinl(reduce_f64(x));
}

long double cospil(long double x) {
	return cosl(reduce_f64(x));
}

long double tanpil(long double x) {
	return tanl(reduce_f64(x));
}
