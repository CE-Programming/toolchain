/************************************************************************/
/*                                                                      */
/*                Copyright (C) 1999-2008 by Zilog, Inc.                */
/*                                                                      */
/************************************************************************/
/*
    C program for floating point sin/cos.
    Calls modf.
    There are no error exits.
    Coefficients are #3370 from Hart & Cheney (18.80D).
*/
#include <math.h>

#define two_over_pi  0.63661977236758134L
#define p0           0.135788409787738e8L
#define p1          -0.494290810090284e7L
#define p2           0.440103053537527e6L
#define p3          -0.138472724998245e5L
#define p4           0.145968840666577e3L
#define q0           0.864455865292253e7L
#define q1           0.408179225234330e6L
#define q2           0.946309610153821e4L
#define q3           0.132653490878614e3L

/**
 * @remarks Approximate minimum ulp:
 * ulp of +57 at +0x1.92024117109b8p+0 (|x| < pi/2)
 */
long double _f64_sinus(unsigned char quad, long double x)
{
    long double x_trunc;
    long double ysq;
    long double y;
    long double temp1, temp2;
    x = x * two_over_pi;
    y = modfl(x, &x_trunc);
    quad = (quad + (unsigned char)x_trunc) & 0x3;
    if (quad & 0x1) {
        y = 1.0L - y;
    }
    if (quad & 0x2) {
        y = -y;
    }
    ysq = y * y;
    temp1 = ((((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0)*y;
    temp2 = ((((ysq+q3)*ysq+q2)*ysq+q1)*ysq+q0);
    return (temp1 / temp2);
}

long double sinl(long double arg) {
    if (fabsl(arg) < 0x1.0p-27L) {
        return arg;
    }
    return  _f64_sinus(signbit(arg) ? 2 : 0, fabsl(arg));
}

long double cosl(long double arg) {
    return _f64_sinus(1, fabsl(arg));
}
