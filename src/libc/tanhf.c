/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
/*
	tanh(arg) computes the hyperbolic tangent of its floating
	point argument.

	sinh and cosh are called except for large arguments, which
	would cause overflow improperly.
*/

#include <math.h>

float _tanhf_c(float arg)
{
	float sign;

	sign = 1.;
	if(arg < 0.){
		arg = -arg;
		sign = -1.;
	}

	if(arg > 21.)
		return(sign);

	return(sign*sinhf(arg)/coshf(arg));
}

double _tanh_c(double) __attribute__((alias("_tanhf_c")));
