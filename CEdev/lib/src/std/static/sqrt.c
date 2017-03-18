/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                              Zilog, Inc.                             */
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

#include <errno.h>
#include <math.h>

extern double sqrtf( double value );

// sqrt - Standard C library routine
// sqrt returns the square root of its floating point argument.
//
// Arguments:
//   value     - the floating point argument
//
// Returns:
//   - the square root (or zero if the argument is negative)
//

double sqrt( double value ) {
	if ( value < 0.0 ) {
		errno = EDOM;
		return 0.0;
	}
	return sqrtf( value );
}
