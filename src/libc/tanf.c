/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                             Zilog, Inc.                              */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/
/*
    floating point tangent

    A series is used after range reduction.
    Coefficients are #4285 from Hart & Cheney. (19.74D)
*/

#include <errno.h>
#include <math.h>
#include <stdbool.h>

#define four_mul_invpi 1.27323954473516f

/**
 * @note These coefficients are for float64
 */
#define p0 -0.130682026475483e+5f
#define p1  0.105597090171495e+4f
#define p2 -0.155068565348327e+2f
#define p3  0.342255438724100e-1f
#define p4  0.338663864267717e-4f
#define q0 -0.166389523894712e+5f
#define q1  0.476575136291648e+4f
#define q2 -0.155503316403171e+3f

/**
 * @remarks Minimum ulp:
 * ulp of -5  at +0x1.82c9b0p-1 (-1.0f < x < 1.0f)
 * ulp of -24 at +0x1.7fd63ap+0 (-1.5f < x < 1.5f)
 *
 * See the purple line for relative precision (lag warning):
 * https://www.desmos.com/calculator/c0zs4b8sqk
 */
float _tanf_c(float arg)
{
    float temp, e, x, xsq;
    bool flag, sign;
    int i;

    flag = false;
    sign = signbit(arg);
    x = fabsf(arg);

    if (x < 0x1.0p-12f) {
        return arg;
    }

    x *= four_mul_invpi; /*overflow?*/
    x = modff(x, &e);
    i = (int)e;

    switch(i % 4) {
        case 1:
            x = 1.0f - x;
            flag = true;
            break;
            
        case 2:
            sign = !sign;
            flag = true;
            break;

        case 3:
            x = 1.0f - x;
            sign = !sign;
            break;

        case 0:
            break;
    }

    xsq = x*x;
    temp = ((((p4*xsq+p3)*xsq+p2)*xsq+p1)*xsq+p0)*x;
    temp = temp/(((xsq+q2)*xsq+q1)*xsq+q0);

    if (flag) {
        if (temp == 0.0f) {
            errno = ERANGE;
            temp = HUGE_VALF;
        } else {
            temp = 1.0f/temp;
        }
    }
    if (sign) {
        temp = -temp;
    }
    return temp;
}

double _tan_c(double) __attribute__((alias("_tanf_c")));
