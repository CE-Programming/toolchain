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

#define two_over_pi  0.636619772367581
#define p0           0.135788409787738e8
#define p1           -0.494290810090284e7
#define p2           0.440103053537527e6
#define p3           -0.138472724998245e5
#define p4           0.145968840666577e3
#define q0           0.864455865292253e7
#define q1           0.408179225234330e6
#define q2           0.946309610153821e4
#define q3           0.132653490878614e3

float sinus(float arg, int quad)
{
    float e, f;
    int k;
    float ysq;
    float x,y;
    float temp1, temp2;

    x = arg;
    if(x<0) {
        x = -x;
        quad = quad + 2;
    }
    x = x*two_over_pi; /*underflow?*/
    if(x>32764){
        y = modff(x,&e);
        e = e + quad;
        modff(0.25*e,&f);
        quad = e - 4*f;
    }else{
        k = x;
        y = x - k;
        quad = (quad + k) & 03;
    }
    if (quad & 01)
        y = 1-y;
    if(quad > 1)
        y = -y;

    ysq = y*y;
    temp1 = ((((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0)*y;
    temp2 = ((((ysq+q3)*ysq+q2)*ysq+q1)*ysq+q0);
    return(temp1/temp2);
}

float _sinf_c(float arg) {
    return sinus(arg, 0);
}

double _sin_c(double) __attribute__((alias("_sinf_c")));
