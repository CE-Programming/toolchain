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
* _u_stoa - convert a short to a number of base rad
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
void _u_stoa(short n)
{
  _u_ltoa((long)n);
}
#else
char _mt_stoa(short n,char* __print_buff,struct fmt_type* print_fmt)
{
  return(_mt_ltoa((long)n,__print_buff,print_fmt));
}
#endif

