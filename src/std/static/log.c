/************************************************************************/
/*									*/
/*                      Copyright (C)1999-2008 by Zilog, Inc.               */
/*                                                                      */
/************************************************************************/
/*
	log returns the natural logarithm of its floating
	point argument.

	The coefficients are #2705 from Hart & Cheney. (19.38D)

	It calls frexp.
*/

#include <errno.h>
#include <math.h>

#define	log2	0.693147180559945e0
#define	ln10	2.30258509299404
#define	sqrto2	0.707106781186548e0
#define	p0	-0.240139179559211e2
#define	p1	0.309572928215377e2
#define	p2	-0.963769093368687e1
#define	p3	0.421087371217980e0
#define	q0	-0.120069589779605e2
#define	q1	0.194809660700890e2
#define	q2	-0.891110902798312e1

double log( double arg )
{
	double x,z, zsq, temp;
	int exp;

	if ( arg <= 0.0 ){
		errno = EDOM;
		return -HUGE_VAL;
	}
    x = frexp( arg, & exp );
	if ( x < sqrto2 ){
		x *= 2;
		exp--;
	}

	z = (x-1)/(x+1);
	zsq = z*z;

	temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
	temp = temp/(((1.0*zsq + q2)*zsq + q1)*zsq + q0);
	temp = temp*z + exp*log2;
	return temp;
}

