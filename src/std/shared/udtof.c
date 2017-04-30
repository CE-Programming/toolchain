/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>
#include <ctype.h>
#include <string.h>
#include <float.h>

#ifndef _MULTI_THREAD
struct flt_info _info;

static char * write_f_digits(char * s, signed char exp, signed char ndig);
static char * write_e_digits(char * s, signed char ndig);
static char * write_exponent(char * s, char e, signed char exp);

#else
static char * write_f_digits(char * s, struct fmt_type* pfmt,struct flt_info* pinfo,signed char exp, signed char ndig);
static char * write_e_digits(char * s, struct flt_info* pinfo,signed char ndig);
static char * write_exponent(char * s, char e, signed char exp);
#define __print_fmt (*fmt)
#endif

typedef long reg_t;
typedef unsigned long ureg_t;


/*************************************************
*
* _u_dtof - convert a double float to ASCII in f format
*
* Inputs:
*	n - value to be converted
*	s - target char array
*	fmt - format structure with conversion info
*
* Locals:
*	ndig - The number of significant digits to print.
*		Assumed to lie in the range [0,127].
*		For e format, this is 1 + precision.
*		For f format, this is 1 + precision + exp.
*
* Returns:
*	next address past the end of the string
*
*************************************************/
#ifndef _MULTI_THREAD
void _u_dtof(double n)
#else
char _mt_dtof(double n,char* __print_buff,struct fmt_type* fmt)
#endif
{
  register reg_t ndig;
  register reg_t rdig;
  register reg_t e;
  char *  s = __print_buff;
#ifdef _MULTI_THREAD
  struct flt_info _info;
  char __print_leading_char = '\0';
#endif

  if (__print_fmt.precision < 0)
    __print_fmt.precision = DEFAULT_PRECISION;

  if (__print_fmt.field_width < 0)
  {
    __print_fmt.flags |= FMT_FLAG_MINUS;
    __print_fmt.field_width = -__print_fmt.field_width;
  }
  rdig = ndig = __print_fmt.precision + 1;
  _u_flt_info(n,&_info);
  if ((__print_fmt.type == 'f') && (_info.exp > 0))
    rdig += _info.exp;		// May be <0.

  if (rdig > FLT_DIG)
    _u_flt_rnd(&_info, FLT_DIG+1);	// Round to the last significant digit.
  else
    _u_flt_rnd(&_info, rdig);		// Round into the last digit printed.

  if (__print_fmt.type == 'f' && (_info.exp > 0))
  {
     ndig += _info.exp;
  }

  if (_info.flags & FLT_INFO_SIGN)
    e = '-';
  else if (__print_fmt.flags & FMT_FLAG_PLUS)
    e = '+';
  else if (__print_fmt.flags & FMT_FLAG_SPACE)
    e = ' ';
  else
   e = '\0';
  if (__print_fmt.flags & FMT_FLAG_PAD_ZERO)
    __print_leading_char = e;
  else if (e)
    *(s++) = e;

  if (_info.flags & FLT_INFO_INF)
  {
    /* This is infinity (+ or -). */
    if (__print_fmt.flags & FMT_FLAG_UPPERCASE)
      strcpy(s,"INF");
    else
      strcpy(s,"inf");
    goto out;
  }

  if (_info.flags & FLT_INFO_NAN)
  {
    /* This is not a number (+ or -). */
    if (__print_fmt.flags & FMT_FLAG_UPPERCASE)
      strcpy(s,"NAN");
    else
      strcpy(s,"nan");
    goto out;
  }

  if (__print_fmt.type == 'e')
#ifndef _MULTI_THREAD
    s = write_e_digits(s, ndig);
#else
    s = write_e_digits(s,&_info,ndig);
#endif
  if (__print_fmt.type == 'f')
#ifndef _MULTI_THREAD
    s = write_f_digits(s, _info.exp, ndig);
#else
    s = write_f_digits(s,fmt,&_info,_info.exp,ndig);
#endif

  /* If g format and not #, strip of trailing zeros. */
  if (__print_fmt.flags & FMT_FLAG_STRIP)
  {
    __print_fmt.pad_post_fract = 0;
    while (s[-1] == '0')	/* strip off trailing zero's */
      --s;
	if (s[-1] == '.')
	  __print_fmt.pad_pre_fract = 0;
  }
  /* Strip off the trailing decimal point, unless prevented by #. */
  if (s[-1] == '.' && 
      ((__print_fmt.pad_pre_fract+__print_fmt.pad_post_fract) == 0) &&
      !(__print_fmt.flags & FMT_FLAG_POUND))
    --s;

  if (__print_fmt.type == 'e')
  {
    e = __print_fmt.flags & FMT_FLAG_UPPERCASE ? 'E' : 'e';
    s = write_exponent(s, e, _info.exp);
  }

  *s = '\0';
out:;
#ifdef _MULTI_THREAD
  return __print_leading_char;
#endif
}

#ifdef _MULTI_THREAD
#define _info (*pinfo)
#endif

/*
 * exp+1- counts the number of digits to the left of the decimal point
 * ndig	- counts the number of significant digits to print.
 */
#ifndef _MULTI_THREAD
static char * write_f_digits(char * s, signed char exp, signed char ndig)
#else
static char * write_f_digits(char * s, struct fmt_type* fmt,struct flt_info* pinfo,signed char exp, signed char ndig)
#endif
{
  ureg_t i = 0;

  /* Emit a leading zero, if needed. */
  if (exp < 0) {
    *(s++) = '0';
	--ndig;
  }

  while (exp >= 0 && i < MAXDIGITS)
  {
    *(s++) = _info.digits[i++] + '0';
    --ndig; --exp;
  }
  __print_fmt.pad_at = s;
  if (exp >= 0) {
    __print_fmt.pad_whole = exp+1;
    ndig -= (exp+1);
	exp = -1;
  }

  *(s++) = '.';


  if (exp < -1) {
    if (ndig > (-exp-1)) {
      __print_fmt.pad_pre_fract = -(exp+1);
	  ndig -= -(exp+1);
	  exp = -1;
    }
    else {
      __print_fmt.pad_pre_fract = ndig;
	  ndig = 0;
    }
  } 
  while (ndig > 0 && i < MAXDIGITS)
  {
    *(s++) = _info.digits[i++] + '0';
    --ndig;
  }
  if (ndig > 0) {
    __print_fmt.pad_post_fract =ndig;
	ndig = 0;
  }
 
  return s;
}

#ifndef _MULTI_THREAD
static char * write_e_digits(char * s, signed char ndig)
#else
static char * write_e_digits(char * s,struct flt_info* pinfo, signed char ndig)
#endif
{
  ureg_t i = 0;

  /* Emit the single digit to the left of the decimal point. */
  *(s++) = _info.digits[i++] + '0';
  --ndig;

  /* Emit the decimal point. */
  *(s++) = '.';

  /* Emit the digits. */
  while (ndig-- > 0 && i < MAXDIGITS)
    *(s++) = _info.digits[i++] + '0';

  return s;
}

static char * write_exponent(char * s, char e, signed char exp)
{
  /* Emit the exponent specifier. */
  *(s++) = e;

  /* Emit the exponent sign. */
  if (exp < 0) {
    *(s++) = '-';
    exp = -exp;
  }
  else
    *(s++) = '+';

  /* Emit the two-digit exponent. */
  /* For 4-byte floats, the exponent is between -37 and +38, or simply 0
     to 38 after folding. */
  *(s++) = exp / 10 + '0';
  *(s++) = exp % 10 + '0';

  return s;
}
