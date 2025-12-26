#if PREFER_CE_LIBC

asm
(
    "\t.global _floorf\n"
    "\t.type _floorf, @function\n"
    "\t.equ _floorf, 0x0220F4\n"
    "\t.global _floor\n"
    "\t.type _floor, @function\n"
    "\t.equ _floor, _floorf\n"
);

#else

/************************************************************************/
/*                                                                      */
/*                 Copyright (C) 2000-2008 Zilog, Inc.                  */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/
#include <math.h>

float floorf(float d) {
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

double floor(double) __attribute__((alias("floorf")));

#endif
