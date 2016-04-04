/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <format.h>
#include <stdarg.h>
#include <stddef.h>

/*************************************************
*
* sscanf - scan from a string
*
* Inputs:
*	string - string to print to
*	fmt - format string
*	args - argument list
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/
int sscanf(char *string,char *fmt,...)
{
  va_list ap;

  if(string == NULL)
	  return EOF;

  va_start(ap,fmt);
#ifndef _MULTI_THREAD
  return(_u_scan(string,fmt,ap));
#else
  return(_mt_sscan(string,fmt,ap));
#endif
}
