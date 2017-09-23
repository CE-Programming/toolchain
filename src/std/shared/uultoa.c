/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>

#ifndef _PTR_
#define _PTR_ *
#endif

/*************************************************
*
* _u_ultoa - convert an unsigned long to a number
*	    of base rad
*
* Inputs:
*	ulg - unsigned long to be converted
*	str - target char array
*	rad - radix
*	fmt - format structure with conversion info
*
* Returns:
*	next address past the end of the string
*
*************************************************/

void __print_sendstring(char *sp);

#ifndef _MULTI_THREAD
void _u_ultoa(unsigned long n)
#else
void _mt_ultoa(unsigned long n,char* __print_buff,struct fmt_type* print_fmt)
#define __print_fmt (*print_fmt)
#endif
{
  unsigned char a;
  unsigned char t;
  char _PTR_ s = __print_buff;
  unsigned char nz = (n != 0);
  char rad;

  a = 'A';
  switch (__print_fmt.type)
  {
  default:
  case 'd':
  case 'i':
  case 'u':
    rad = 10;
    break;
  case 'o':
    rad = 8;
    break;
  case 'x':
  case 'p':
    if ( !(__print_fmt.flags&FMT_FLAG_UPPERCASE))
      a = 'a';
    // Fall into next case
  case 'X':
    rad = 16;
    break;
  }

  do
    {	/* generate digits in reverse order */
    t = n % (unsigned char)rad;
    if (t > 9)
      *(s++) = (t - (unsigned char)10) + a;
    else
      *(s++) = t + (unsigned char)'0';
    }  while (n /= rad);

  while (s - __print_buff < (unsigned char) __print_fmt.precision) {
    *(s++) = '0';
  }
  if (__print_fmt.flags & FMT_FLAG_POUND) {
    if (nz) {
      if (rad == (char)16) {
	*(s++) = ('X'-'A')+a;
	*(s++) = '0';
      }
      else if (rad == (char)8) {
	*(s++) = '0';
      }
    }
  }

  // ISO Spec:  If a precision is specified  the zero flag is ignored
  if (__print_fmt.precision )
    __print_fmt.flags &= ~FMT_FLAG_PAD_ZERO;

  *s = '\0';

  _u_reverse(__print_buff);
#ifndef _MULTI_THREAD
  __print_sendstring(__print_buff);
#endif
}

