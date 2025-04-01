/************************************************************************/
/*																	  */
/*					  Copyright (C)1987-2008 by					   */
/*							 Zilog, Inc.							  */
/*																	  */
/*						 San Jose, California						 */
/*																	  */
/************************************************************************/
/*
	sinh(arg) returns the hyperbolic sine of its floating-
	point argument.

	The exponential function is called for arguments
	greater in magnitude than 0.5.

	A series is used for arguments smaller in magnitude than 0.5.
	The coefficients are #2029 from Hart & Cheney. (20.36D)

	cosh(arg) is computed from the exponential function for
	all arguments.
*/

#include <math.h>

/**
 * @remarks Minimum ulp:
 * ulp of -1  at +0x1.39a3fep-12 with ideal expf (|x| < 21.0f)
 * ulp of -18 at +0x1.0a049cp+4  with current expf (|x| < 21.0f)
 */
float _coshf_c(float arg) {
	float val;
	arg = fabsf(arg);

	val = expf(arg);

	if (arg > 21.0f) {
		return val / 2.0f;
	}

	val += expf(-arg);
	val /= 2.0f;
	return val;
}

double _cosh_c(double) __attribute__((alias("_coshf_c")));

