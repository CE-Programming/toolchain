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

float _powf_c(float arg1, float arg2) {
    float result;
    long temp;

    if ( arg1 > 0.0 ){
        return expf( arg2 * logf( arg1 ) );
    }
    if ( arg1 < 0.0 ){
        temp = arg2;
        if ( temp == arg2 ){
            result = expf( arg2 * logf( -arg1 ) );
            return temp & 1 ? -result : result;
        }
        errno = EDOM;
    }
    if ( arg2 <= 0.0 ){
        errno = EDOM;
    }
    return 0.0;
}

double _pow_c(double, double) __attribute__((alias("_powf_c")));
