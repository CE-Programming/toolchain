/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>
#include <ctype.h>
//#include <sio.h>
#include <float.h>


struct flt_info _info;
typedef long reg_t;
typedef unsigned long ureg_t;

/*************************************************
*
* _u_dtoe - convert a double float to ASCII in e format
*
* Inputs:
*	n - value to be converted
*	s - target char array
*	__print_fmt - format structure with conversion info
*
* Locals:
*	ndig - The number of significant digits in the output.  This is
*		assumed to be less than 128!
*
* Returns:
*	next address past the end of the string
*
*************************************************/
char * _u_dtoe(double n)
{
  register ureg_t i;
  register ureg_t ndig;
  register reg_t exp;
  char *  s = __print_buff;

  /* One digit to the left of the decimal point, and precision after. */
  ndig = __print_fmt.precision + 1;
  _u_flt_info(n,&_info);
  if (ndig > FLT_DIG) 
    _u_flt_rnd(&_info,FLT_DIG);
  else
    _u_flt_rnd(&_info,ndig);

  if (_info.flags == FLT_INFO_SIGN)
    *(s++) = '-';
  else if (__print_fmt.flags & FMT_FLAG_PLUS)
    *(s++) = '+';
  else if (__print_fmt.flags & FMT_FLAG_POUND)
    *(s++) = ' ';

  *(s++) = _info.digits[0] + '0';
  if (__print_fmt.precision != 0)
    *(s++) = '.';
  for (i=1; i < ndig; i++)
    *(s++) = _info.digits[(unsigned char) i] + '0';

  if (!(__print_fmt.flags & FMT_FLAG_POUND) &&
      (__print_fmt.type == 'g' || __print_fmt.type == 'G')) {
    while (s[-1] == '0')	/* strip off trailing zero's */
      --s;
    if (s[-1] == '.')
      --s;			/* strip off . */
  }
  else if (ndig == 1 && !(__print_fmt.flags & FMT_FLAG_POUND))
    --s;	/* remove decimal point */
  *(s++) = isupper(__print_fmt.type) ? 'E' : 'e';

  exp = _info.exp;
  if (exp < 0) {
    *(s++) = '-';
    exp = -exp;
  }
  else
    *(s++) = '+';

  /* For 4-byte floats, the exponent is between -37 and +38, or simply 0
     to 38 after folding. */
  /* e format always prints two digits in the exponent. */
  *(s++) = exp / 10 + '0';
  *(s++) = exp % 10 + '0';

  *s = '\0';
  return(s);
}
