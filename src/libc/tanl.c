/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
/*
    floating point tangent

    A series is used after range reduction.
    Coefficients are #4285 from Hart & Cheney. (19.74D)
*/

#include <errno.h>
#include <math.h>
#include <stdbool.h>

#define four_mul_invpi 1.27323954473516L

#define p0 -0.130682026475483e+5L
#define p1  0.105597090171495e+4L
#define p2 -0.155068565348327e+2L
#define p3  0.342255438724100e-1L
#define p4  0.338663864267717e-4L
#define q0 -0.166389523894712e+5L
#define q1  0.476575136291648e+4L
#define q2 -0.155503316403171e+3L

/**
 * @remarks Minimum relative precision of:
 * 2^-45.21 at +1.299439430e+00 (-1.3L < x < +1.3L)
 *
 * See the purple line for relative precision (lag warning):
 * https://www.desmos.com/calculator/c0zs4b8sqk
 */
long double tanl(long double arg)
{
    long double temp, e, x, xsq;
    bool flag, sign;
    int i;

    flag = false;
    sign = signbit(arg);
    x = fabsl(arg);

	if (x < 0x1.0p-26L) {
		return arg;
	}

    x *= four_mul_invpi; /*overflow?*/
    x = modfl(x, &e);
    i = (int)e;

    switch(i % 4) {
        case 1:
            x = 1.0L - x;
            flag = true;
            break;
            
        case 2:
            sign = !sign;
            flag = true;
            break;

        case 3:
            x = 1.0L - x;
            sign = !sign;
            break;

        case 0:
            break;
    }

    xsq = x*x;
    temp = ((((p4*xsq+p3)*xsq+p2)*xsq+p1)*xsq+p0)*x;
    temp = temp/(((xsq+q2)*xsq+q1)*xsq+q0);

    if (flag) {
        if (temp == 0.0L) {
            errno = ERANGE;
            temp = HUGE_VALL;
        } else {
            temp = 1.0L/temp;
        }
    }
    if (sign) {
        temp = -temp;
    }
    return temp;
}
