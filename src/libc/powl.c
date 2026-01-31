/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                             Zilog, Inc.                              */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/

#include <errno.h>
#include <math.h>

long double powl(long double x, long double y) {
    long double result;
    long temp;

    if ( x > 0.0L ){
        return expl( y * logl( x ) );
    }
    if ( x < 0.0L ){
        temp = (long)y;
        if ( (long double)temp == y ){
            result = expl( y * logl( -x ) );
            return temp & 1 ? -result : result;
        }
        errno = EDOM;
    }
    if ( y <= 0.0L ){
        errno = EDOM;
    }
    return 0.0L;
}
