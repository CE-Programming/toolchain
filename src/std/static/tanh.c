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

double tanh(double arg)
{
    return tanhf(arg);
}

float tanhf(float arg)
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
