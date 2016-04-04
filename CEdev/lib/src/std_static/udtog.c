/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>

/*************************************************
*
* _u_dtog - convert a double float to ASCII in g format
*
* Inputs:
*	n - value to be converted
*	s - target char array
*	fmt - format structure with conversion info
*
* Returns:
*	next address past the end of the string
*
*************************************************/
#ifndef _MULTI_THREAD
void _u_dtog(double n)
#else
char _mt_dtog(double n,char* __print_buff,struct fmt_type* fmt)
#define __print_fmt (*fmt)
#define _u_dtof(n) _mt_dtof(n,__print_buff,fmt)
#endif
{
  struct flt_info _info;

  _u_flt_info(n, &_info);

  if (__print_fmt.precision < 0)
    __print_fmt.precision = 0;

  if (__print_fmt.field_width < 0)
  {
    __print_fmt.flags |= FMT_FLAG_MINUS;
    __print_fmt.field_width = -__print_fmt.field_width;
  }

  if (!(__print_fmt.flags & FMT_FLAG_POUND))
    __print_fmt.flags |= FMT_FLAG_STRIP;

  // ISO Spec: The precision is the maximal number of significant digits
  //           if the precision is zero it is taken as one.
  if (!__print_fmt.precision)
    __print_fmt.precision=1;

  if (   _info.exp < MINEXP
      || _info.exp >= __print_fmt.precision)
  {
    --__print_fmt.precision;
    __print_fmt.type = 'e';
  }
  else
  {
    __print_fmt.precision -= (1 + _info.exp);
    __print_fmt.type = 'f';
  }

#ifndef _MULTI_THREAD
  _u_dtof(n);
#else
  return(_u_dtof(n));
#endif
}
