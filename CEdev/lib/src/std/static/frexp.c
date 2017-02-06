/************************************************************************/
/*                                                                      */
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

#include <math.h>

typedef union
{
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

// frexp - Standard C library routine
// frexp returns the exponent and mantissa of its floating point
// argument.
//
// Arguments:
//   value     - the floating point argument
//   pExponent - pointer to the returned exponent
//
// Returns:
//   - a floating point number between 0.5 and 1.0 (or zero if
//     the input argument is zero)
//
double frexp( double value, int *pExponent )
{
    Ieee754 floating;
    long    exponentBits = 0;

    floating.value = value;
    if ( value != 0.0 )
    {
        exponentBits   = (floating.bits
                          & ((unsigned long) exponent_mask << exponent_shift))
                       - ((exponent_base - 1L) << exponent_shift);
        floating.bits -= exponentBits;  // adjust exponent
    }
    if ( pExponent != 0 )
    {
        *pExponent = exponentBits >> exponent_shift;
    }
    return floating.value;
}
