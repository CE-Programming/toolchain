/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                              Zilog, Inc.                             */
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

#include <math.h>

typedef union {
    float             value;
    unsigned long     bits;
} Ieee754;

enum
{   //  The IEEE 754 format is:
    //  SEEEEEEE EMMMMMMM MMMMMMMM MMMMMMMM
    //  (with an implicit mantissa high-order 1-bit.)
    mastissa_shift = 0,
    mastissa_bits  = 23,
    exponent_bits  = 8,
    exponent_shift = mastissa_shift + mastissa_bits,
    sign_shift     = exponent_shift + exponent_bits,
    exponent_mask  = (1 << exponent_bits) -1,  // shifted = 0x7F800000
    exponent_max   = (1 << exponent_bits) -1,
    exponent_base  = 127,
    exponent_min   = 0
};

/* modf - Standard C library routine
 * modf returns the integral and fractional components of its
 * floating point argument.
 *
 * Arguments:
 *   value     - the floating point argument
 *   pIntegral - pointer to the returned integral component
 *
 * Returns:
 *   - the fractional component
 */
double modf( double value, double *pIntegral ) {
	Ieee754 integral;
	int     exponent;

	integral.value = value;
	frexp( value, &exponent);
	if ( exponent <= 0 ) {							// set integral portion to zero
		integral.bits = 0;
	} else if ( exponent <= mastissa_bits ) {				// mask out fractional portion
		integral.bits &= -1L << (mastissa_bits - exponent + 1);
	}
	if ( pIntegral != 0 ) {
		*pIntegral = integral.value;
	}
	return value - integral.value;
}
