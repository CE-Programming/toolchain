/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef MATH_H
#define MATH_H

extern double _huge_val;
#define HUGE_VAL _huge_val	               /* overflow error */

#define M_E         2.71828182845904523536     /* e            */
#define M_LOG2E     1.44269504088896340736     /* log2(e)      */
#define M_LOG10E    0.434294481903251827651    /* log10(e)     */
#define M_LN2       0.693147180559945309417    /* ln(2)        */
#define M_LN10      2.30258509299404568402     /* ln(10)       */
#define M_PI        3.14159265358979323846     /* pi           */
#define M_PI_2      1.57079632679489661923     /* pi/2         */
#define M_PI_4      0.785398163397448309616    /* pi/4         */
#define M_1_PI      0.318309886183790671538    /* 1/pi         */
#define M_2_PI      0.636619772367581343076    /* 2/pi         */
#define M_2_SQRTPI  1.12837916709551257390     /* 2/sqrt(pi)   */
#define M_SQRT2     1.41421356237309504880     /* sqrt(2)      */
#define M_SQRT1_2   0.707106781186547524401    /* 1/sqrt(2)    */
#define M_LOG_2M_PI 1.83787706640934548        /* log2(M_PI)   */

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
double floor(double x);
double fabs(double x);
double fmod(double x, double y);
double round(double x);

double frexp(double value, int *exp);
double modf(double value, double *iptr);

int isinf(double n);
int isnan(double n);
int finite(double n);

double tgamma(double x);
double log2(double x);

#endif
