/* Copyright (c) 2000-2008 Zilog, Inc. */
#include <math.h>
#include "__float64_constants.h"

long double atan2l(long double arg1, long double arg2) {
	long double f64_satan(long double);

	if ((arg1+arg2)==arg1) {
		if (arg1 >= 0.0L) {
			return (F64_PI2);
		} else {
			return (-F64_PI2);
		}
	} else if (arg2 < 0.0L) {
		if(arg1 >= 0.0L) {
			return (F64_PI - f64_satan(-arg1/arg2));
		} else {
			return (-F64_PI + f64_satan(arg1/arg2));
		}
	} else if (arg1 > 0.0L) {
		return (f64_satan(arg1/arg2));
	} else {
		return (-f64_satan(-arg1/arg2));
	}
}
