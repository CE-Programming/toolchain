/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef MATH_H
#define MATH_H

extern double _huge_val;
#define HUGE_VAL _huge_val	/* overflow error */

double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y,double x);
double cos(double x);
double sin(double x);
double tan(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double exp(double x);
double ldexp(double x, int exp);
double log(double x);
double log10(double x);
double pow(double x,double y);
double sqrt(double x);
double ceil(double x);
double fabs(double x);
double floor(double x);
double fmod(double x, double y);

double frexp(double value, int * exp);
double modf(double value, double * iptr);

#endif
