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

#define two_over_pi  0.63661977236758134f
#define p0           0.135788409787738e8f
#define p1           -0.494290810090284e7f
#define p2           0.440103053537527e6f
#define p3           -0.138472724998245e5f
#define p4           0.145968840666577e3f
#define q0           0.864455865292253e7f
#define q1           0.408179225234330e6f
#define q2           0.946309610153821e4f
#define q3           0.132653490878614e3f

/**
 * @remarks Minimum ulp:
 * ulp of -5 at +0x1.fe2dd0p-9 (2^-10 < |x| < pi/2)
 *
 * @note positive arguments only
 * @warning undefined behaviour if |x| > LONG_MAX
 */
float _f32_sinus(unsigned char quad, float x) {
    float x_trunc;
    float ysq;
    float y;
    float temp1, temp2;

    x = x * two_over_pi;
    y = modff(x, &x_trunc);
    quad = (quad + (unsigned char)x_trunc) & 0x3;
    if (quad & 0x1) {
        y = 1.0f - y;
    }
    if (quad & 0x2) {
        y = -y;
    }

    ysq = y * y;
    temp1 = ((((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0)*y;
    temp2 = ((((ysq+q3)*ysq+q2)*ysq+q1)*ysq+q0);
    return(temp1/temp2);
}
