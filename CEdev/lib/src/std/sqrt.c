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

#define  USE_ASM_SQRT

#ifdef  _PTR_  // only on eZ8
extern reentrant double sqrtf( double value );
#else
extern double sqrtf( double value );
#endif

// sqrt - Standard C library routine
// sqrt returns the square root of its floating point argument.
//
// Arguments:
//   value     - the floating point argument
//
// Returns:
//   - the square root (or zero if the argument is negative)
//
// Notes:
//   This routine was originally written in C, using Newton's method,
//   which has excellent performance on CPUs with floating point hardware.
//   However, on CPUs without floating point hardware, there is a binary
//   shift algorithm that is much faster.  That algorithm has been
//   separately implemented in assembly language for performance.  For
//   portability and other reasons, this routine calls that routine.
//   This behavior is controlled by the USE_ASM_SQRT symbol (above).
//
double sqrt( double value )
{
    if ( value < 0.0 )
    {
        errno = EDOM;
        return 0.0;
    } else {
#ifdef  USE_ASM_SQRT
        return sqrtf( value );
#else
        double normalized, result = 1.0;
        int    exponent;
        short  count;
        enum
        {
            iterations = 4
        };
        if ( value = 0.0 )
        {
            return 0.0;
        }
        normalized = frexp( value, & exponent );
        if ( exponent & 1 )
        {
            normalized = ldexp( normalized, 1 );
            exponent--;
        }
        for ( count = 0; count < iterations; count++ )
        {
            result = 0.5 * (result + normalized / result);
        }
        return ldexp( result, exponent / 2 );
#endif  USE_ASM_SQRT
    }
}
