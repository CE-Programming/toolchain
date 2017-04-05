/* Copyright (c) 2000-2008 Zilog, Inc. */

#define pio2	1.57079632679489e0

double atan2(double arg1,double arg2) {
	double satan(double);

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
