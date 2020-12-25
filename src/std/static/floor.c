/************************************************************************/
/*									*/
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <math.h>


double floor(double d) {
	return floorf(d);
}

float floorf(float d) {
	float fraction;

	if (d<0.0) {
		d = -d;
                fraction = modff(d, &d);
		if (fraction != 0.0)
			d += 1;
		d = -d;
	} else {
                fraction = modff(d, &d);
	}
	return(d);
}
