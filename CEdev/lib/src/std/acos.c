/* Copyright (c) 2000-2008 Zilog, Inc. */

/**
 * asin(arg) and acos(arg) return the arcsin, arccos,
 * respectively of their arguments.
 */

#include	<errno.h>
#include	<math.h>

#define pio2  1.57079632679490

double acos(double arg) {

	if((arg > 1.) || (arg < -1.)) {
		errno = EDOM;
		return(0.);
	}

	return(pio2 - asin(arg));
}
