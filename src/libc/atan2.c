/* Copyright (c) 2000-2008 Zilog, Inc. */
#include <math.h>

#define pio2	1.57079632679489e0

float _atan2f_c(float arg1,float arg2) {
	float satan(float);

	if((arg1+arg2)==arg1) {
		if(arg1 >= 0.) {
			return(pio2);
		} else {
			return(-pio2);
		}
	} else if(arg2 < 0.) {
		if(arg1 >= 0.) {
			return(pio2+pio2 - satan(-arg1/arg2));
		} else {
			return(-pio2-pio2 + satan(arg1/arg2));
		}
	} else if(arg1 > 0) {
		return(satan(arg1/arg2));
	} else {
		return(-satan(-arg1/arg2));
	}
}

double _atan2_c(double, double) __attribute__((alias("_atan2f_c")));
