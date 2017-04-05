/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>

/*************************************************
*
* _u_ustoa - convert an unsigned short to a number of base rad
*
* Inputs:
*	int - int to be converted
*	str - target char array
*	rad - radix
*	fmt - format structure with conversion info
*
* Returns:
*	next address past the end of the string
*
*************************************************/
#ifndef _MULTI_THREAD
void _u_ustoa(unsigned short n)
{
  _u_ultoa((unsigned long)n);
}
#else
void _mt_ustoa(unsigned short n,char* __print_buff,struct fmt_type* print_fmt)
{
  _mt_ultoa((unsigned long)n,__print_buff,print_fmt);
}
#endif

