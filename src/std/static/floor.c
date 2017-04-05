/************************************************************************/
/*									*/
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <math.h>

double floor(double d) {
	double fraction;

	if (d<0.0) {
		d = -d;
                fraction = modf(d, (double *)&d);
		if (fraction != 0.0)
			d += 1;
		d = -d;
	} else {
                fraction = modf(d, (double *)&d);
	}
	return(d);
}
