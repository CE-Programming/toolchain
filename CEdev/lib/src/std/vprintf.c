/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <format.h>
#include <stdio.h>
#include <stdarg.h>

/*************************************************
*
* vprintf - print to stdout (variable args)
*
* Inputs:
*	fmt - format string
*	ap - argument list
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/
int vprintf(char _PTR_ fmt,va_list ap)
{
#ifndef _MULTI_THREAD
  // Set up to print to device
  __print_xputch = __print_uputch;
  _u_print((void _PTR_)NULL,fmt,ap);
  // reset to print to sprintf buffer
  __print_xputch = __print_sputch;
#else
  register unsigned char __print_len = _mt_print(fmt,ap);
#endif
  if (__print_len < 0 )
    return -1;
  return __print_len;
}

