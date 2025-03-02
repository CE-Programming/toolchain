/* Copyright (c) 2000-2008 Zilog, Inc. */

/**
 * floating-point arctangent
 *
 * atan returns the value of the arctangent of its
 * argument in the range [-pi/2,pi/2].
 *
 * atan2 returns the arctangent of arg1/arg2
 * in the range [-pi,pi].
 *
 * there are no error returns.
 *
 * coefficients are #5077 from Hart & Cheney. (19.56D)
 */
#include <math.h>

#define sq2p1	2.41421356237309e0
#define sq2m1	0.414213562373095e0
#define pio2	1.57079632679489e0
#define pio4	0.785398163397448e0
#define p4	0.161536412982230e2
#define p3	0.268425481955040e3
#define p2	0.115302935154049e4
#define p1	0.178040631643320e4
#define p0	0.896785974036639e3
#define q4	0.589569705084446e2
#define q3	0.536265374031215e3
#define q2	0.166678381488163e4
#define q1	0.207933497444541e4
#define q0	0.896785974036639e3

/**
 * atan makes its argument positive and
 * calls the inner routine satan.
 */

float _atanf_c(float arg) {
	float satan(float);

	if(arg>0) {
		return(satan(arg));
	} else {
		return(-satan(-arg));
	}
}

double _atan_c(double) __attribute__((alias("_atanf_c")));

/**
 * atan2 discovers what quadrant the angle
 * is in and calls atan.
 */


/**
 * xatan evaluates a series valid in the
 * range [-0.414...,+0.414...].
 */

static float xatan(float arg) {
	float argsq;
	float value;

	argsq = arg*arg;
	value = ((((p4*argsq + p3)*argsq + p2)*argsq + p1)*argsq + p0);
	value = value/(((((argsq + q4)*argsq + q3)*argsq + q2)*argsq + q1)*argsq + q0);
	return(value*arg);
}

/**
 * satan reduces its argument (known to be positive)
 * to the range [0,0.414...] and calls xatan.
 */

float satan(float arg) {
	if(arg < sq2m1) {
		return(xatan(arg));
	} else if(arg > sq2p1) {
		return(pio2 - xatan(1.0/arg));
	} else {
		return(pio4 + xatan((arg-1.0)/(arg+1.0)));
	}
}
