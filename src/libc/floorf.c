/************************************************************************/
/*                                                                      */
/*                 Copyright (C) 2000-2008 Zilog, Inc.                  */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/
#include <math.h>

float _floorf_c(float d) {
    float fraction;

    if (d<0.0) {
        d = -d;
            fraction = modff(d, &d);
        if (fraction != 0.0) {
            d += 1;
        }
        d = -d;
    } else {
        fraction = modff(d, &d);
    }
    return(d);
}

double _floor_c(double) __attribute__((alias("_floorf_c")));
