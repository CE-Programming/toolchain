/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>
#include <string.h>
#include <stdlib.h>
#include <cio.h>

/* Send the contents of __print_buff to the printf/sprintf destination and */
/* update the count of characters output                                   */
/* The compiler may generate direct calls to this to bypass the runtime    */
/* parsing of printf formats.                                              */

#ifndef _MULTI_THREAD
void __print_send()
#else
unsigned char __mt_print_send(char __print_leading_char,char* __print_buff,struct fmt_type* print_fmt)
#define __print_putch putch
#define __print_fmt (*print_fmt)
#endif
{
  int i;
  int i0=0;
  char padch = ' ';
  char* p1;
  char padRight = ((__print_fmt.flags & FMT_FLAG_MINUS) || __print_fmt.field_width < 0);
#ifdef _MULTI_THREAD
  unsigned char __print_len = 0;
#endif

  /*   Output any initial +, -, or space.  This needs to come before any     */
  /*   zeros inserted for padding.                                           */
  if (__print_leading_char)
  {
    __print_putch(__print_leading_char);
    __print_len += 1;
#ifndef _MULTI_THREAD
    __print_leading_char = '\0';
#endif
    i0=1;
  }

        /* look at flag and field width */
        /* and do proper padding.       */

  if (__print_fmt.field_width != 0) {
    padch = ' ';
    if (!padRight)
    {
      if (__print_fmt.flags & FMT_FLAG_PAD_ZERO)
        padch = '0';
      i=abs(__print_fmt.field_width)-strlen(__print_buff)-i0;
      for (;i > 0;--i)
      {
        __print_len++;
        __print_putch(padch);
      }
    }
  }

  for (p1=__print_buff;*p1;++p1)
    __print_putch(*p1);
    __print_len += p1-__print_buff;
    if (padRight)
    {
      i=abs(__print_fmt.field_width)-(p1-__print_buff);
		if(i > 0) {
			__print_len += i;
			for (;i > 0;--i)
			  __print_putch(padch);
		}
    }
    /*  Reset the data manipulated by the compiler, so that no code is needed */
    /*  to set default values.                                                */
    __print_fmt.type = __print_fmt.field_width= __print_fmt.precision= __print_fmt.flags= 0;

#ifdef _MULTI_THREAD
	return __print_len;
#endif
}
