#if PREFER_CE_LIBC

asm
(
    "\t.global _expf\n"
    "\t.type _expf, @function\n"
    "\t.equ _expf, 0x022124\n"
    "\t.global _exp\n"
    "\t.type _exp, @function\n"
    "\t.equ _exp, _expf\n"
);

#else

/************************************************************************/
/*                                                                      */
/*                 Copyright (C) 2000-2008 Zilog, Inc.                  */
/*                                                                      */
/************************************************************************/
/*
    exp returns the exponential function of its
    floating-point argument.

    The coefficients are #1069 from Hart and Cheney. (22.35D)
*/

#include <errno.h>
#include <math.h>
#include "__float32_constants.h"

/**
 * @note These coefficients are for float64
 */
#define p0 0.20803843466947e7f
#define p1 0.30286971697440e5f
#define p2 0.60614853300611e2f
#define q0 0.60027203602388e7f
#define q1 0.32772515180829e6f
#define q2 0.17492876890931e4f

#if 0
#define exp_max_arg 88.723f
#define exp_min_arg -103.28f
#else
/* mantissa is zero for these constants */
#define exp_max_arg 128.0f
#define exp_min_arg -128.0f
#endif

/**
 * @remarks Minimum ulp:
 * ulp of -4  at +0x1.439a98p-1 (-ln(2) < x < +ln(2))
 * ulp of -60 at +0x1.e2681ap+5 (-64.0f < x < +64.0f)
 *
 * See the purple line for relative precision (lag warning):
 * https://www.desmos.com/calculator/zlrmxatxkf
 */
float expf(float arg) {
    float fraction;
    float temp1, temp2, xsq;
    float ent;

    if ( arg == 0.0f){
        return 1.0f;
    }
    if ( arg < exp_min_arg ){
        return 0.0f;
    }
    if ( arg > exp_max_arg ){
        errno = ERANGE;
        return HUGE_VALF;
    }
    arg *= F32_LOG2E;
    ent = floorf( arg );
    fraction = arg - ent - 0.5f;
    xsq = fraction * fraction;
    temp1 = ((p2 * xsq + p1) * xsq + p0) * fraction;
    temp2 = ((xsq + q2) * xsq + q1) * xsq + q0;
    return ldexpf( F32_SQRT2 * (temp2+temp1) / (temp2-temp1), (int)ent );
}

double exp(double) __attribute__((alias("expf")));

#endif
