/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *  Modified by Matt "MateoConLechuga" Waltz for TI84+CE platform
 */
#ifndef FLOAT_H
#define FLOAT_H

#define FLT_RADIX	2	/* radix of exponent representation */

#define FLT_ROUNDS	0	/* addition rounds to nearest       */

/* number of base-FLT_RADIX digits in the mantissa */

#define FLT_MANT_DIG 24
#define DBL_MANT_DIG FLT_MANT_DIG
#define LDBL_MANT_DIG FLT_MANT_DIG

/* number of decimal digits of precision */

#define FLT_DIG 	6
#define DBL_DIG 	FLT_DIG
#define LDBL_DIG	FLT_DIG

/* minimum negative integer such that FLT_RADIX raised to that */
/* power approximates a positive floating point number in the  */
/* range of representable values.                              */

#define FLT_MIN_EXP	(-125)
#define DBL_MIN_EXP	FLT_MIN_EXP
#define LDBL_MIN_EXP	FLT_MIN_EXP

/* maximum integer such that FLT_RADIX raised to that power */
/* approximates a floating point number in the range of     */
/* representable numbers.                                   */

#define FLT_MAX_EXP	128
#define DBL_MAX_EXP	FLT_MAX_EXP
#define LDBL_MAX_EXP	FLT_MAX_EXP

/* maximum integer such that 10 raised to that power    */
/* approximates a floating point number in the range of */
/* representable value ((int)log10(FLT_MAX),etc)        */

#define FLT_MAX_10_EXP	(+38)
#define DBL_MAX_10_EXP	FLT_MAX_10_EXP
#define LDBL_MAX_10_EXP FLT_MAX_10_EXP

/* minimum negative integer such that 10 raised to that power */
/* approximates a positive floating point number in the range */
/* of representable values ((int)log10(FLT_MIN),etc.)         */

#define FLT_MIN_10_EXP	(-37)
#define DBL_MIN_10_EXP	FLT_MIN_10_EXP
#define LDBL_MIN_10_EXP FLT_MIN_10_EXP

/* maximum representable floating point numbers */

#define FLT_MAX 	3.40282347E+38
#define DBL_MAX 	FLT_MAX
#define LDBL_MAX	FLT_MAX

/* minimum positive number x such that 1.0 + x != 1.0 (b ^ (1-p)) */

#define FLT_EPSILON	1.19209290E-07
#define DBL_EPSILON	FLT_EPSILON
#define LDBL_EPSILON	FLT_EPSILON

/* minimum representable positive floating point numbers */

#define FLT_MIN 	1.17549435E-38
#define DBL_MIN 	FLT_MIN
#define LDBL_MIN	FLT_MIN

#endif
