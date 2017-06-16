/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#include <format.h>
#include <string.h>
#include <stdlib.h>

/* Send a string to the printf/sprintf destination                         */
/* The compiler may generate direct calls to this to bypass the runtime    */
/* parsing of printf formats.                                              */

void __print_putch(char ch);

void __print_sendstring(char *sp)
{
  unsigned char i = 0;
  unsigned short j, jmax;
  char* s = sp;
  char padRight = 0;
  if (__print_fmt.field_width != 0)
  {
      padRight = ((__print_fmt.flags & FMT_FLAG_MINUS) || __print_fmt.field_width < 0);
      if (!padRight)
      {
         char pad = strlen(s);
         if (__print_fmt.flags & FMT_FLAG_PRECISION && pad > __print_fmt.precision)
            pad = __print_fmt.precision;

         pad = __print_fmt.field_width-pad;
         while(pad > 0)
         {
           __print_putch(' ');
           i++;
           pad--;
         }
      }
  }
  /* If precision not specified, make it 127 */
  if (!(__print_fmt.flags & FMT_FLAG_PRECISION))
    jmax = 0xffff;
  else
    jmax = (unsigned)__print_fmt.precision;

  for (j=0;j<jmax && *s;j++)
      __print_putch(*s++);
  i += j;
  if (padRight)
  {
     __print_fmt.field_width = abs(__print_fmt.field_width);
     while (i < __print_fmt.field_width)
     {
        __print_putch(' ');
        i++;
     }
  }
  __print_len += i;
  /*  Reset the data manipulated by the compiler, so that no code is needed */
  /*  to set default values.                                                */
  __print_fmt.field_width= __print_fmt.precision= __print_fmt.flags= 0;
}
