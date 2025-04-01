/************************************************************************/
/*																	  */
/*				 Copyright (C) 2000-2008 Zilog, Inc.				  */
/*																	  */
/************************************************************************/
/*
	exp returns the exponential function of its
	floating-point argument.

	The coefficients are #1069 from Hart and Cheney. (22.35D)
*/

#include <errno.h>
#include <math.h>
#include "__float64_constants.h"

#define p0 0.20803843466947e7L
#define p1 0.30286971697440e5L
#define p2 0.60614853300611e2L
#define q0 0.60027203602388e7L
#define q1 0.32772515180829e6L
#define q2 0.17492876890931e4L

#if 0
#define	exp_max_arg 709.79L
#define exp_min_arg -744.45L
#else
/* mantissa is zero for these constants */
#define exp_max_arg 1024.0L
#define exp_min_arg -1024.0L
#endif

/**
 * @remarks Minimum relative precision of:
 * 2^-45.23 at -4.062250536e-12 (-ln(2) < x < +ln(2))
 * 2^-38.55 at -5.115436707e+02 (-512.0L < x < +512.0L)
 *
 * See the purple line for relative precision (lag warning):
 * https://www.desmos.com/calculator/zlrmxatxkf
 */
long double expl(long double arg) {
	long double fraction;
	long double temp1, temp2, xsq;
	long double ent;

	if ( arg == 0.0L ){
		return 1.0L;
	}
	if ( arg < exp_min_arg ){
		return 0.0L;
	}
	if ( arg > exp_max_arg ){
		errno = ERANGE;
		return HUGE_VALL;
	}
	arg *= F64_LOG2E;
	ent = floorl( arg );
	fraction = arg - ent - 0.5L;
	xsq = fraction * fraction;
	temp1 = ((p2 * xsq + p1) * xsq + p0) * fraction;
	temp2 = ((xsq + q2) * xsq + q1) * xsq + q0;
	return ldexpl( F64_SQRT2 * ((temp2+temp1) / (temp2-temp1)), (int)ent );
}
