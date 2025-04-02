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

    if (d < 0.0f) {
        d = -d;
        fraction = modff(d, &d);
        if (fraction != 0.0f) {
            d += 1.0f;
        }
        d = -d;
        return d;
    }
    return truncf(d);
}

double _floor_c(double) __attribute__((alias("_floorf_c")));
