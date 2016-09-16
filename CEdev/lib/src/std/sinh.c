/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
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

#define p0  -0.630767364049772e+6
#define p1  -0.899127202203951e+5
#define p2  -0.289421135598956e+4
#define p3  -0.263056321339750e+2
#define q0  -0.630767364049772e+6
#define q1  0.152151737879002e+5
#define q2  -0.173678953558234e+3

double sinh(double arg) {
	double temp, argsq;
	register int sign;

	sign = 1;
	if(arg < 0) {
		arg = - arg;
		sign = -1;
	}

	if(arg > 21.) {
		temp = exp(arg)/2;
		if (sign>0)
			return(temp);
		else
			return(-temp);
	}

	if(arg > 0.5) {
		return(sign*(exp(arg) - exp(-arg))/2);
	}

	argsq = arg*arg;
	temp = (((p3*argsq+p2)*argsq+p1)*argsq+p0)*arg;
	temp /= (((argsq+q2)*argsq+q1)*argsq+q0);
	return(sign*temp);
}

double cosh(double arg) {
    double val;

	if(arg < 0)
		arg = - arg;
	if(arg > 21.) {
		return(exp(arg)/2);
	}

	val = exp(arg);
	val += exp(-arg);
	val /= 2;
	return(val);
//	return((exp(arg) + exp(-arg))/2);
}
