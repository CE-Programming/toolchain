/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <format.h>
#include <stdio.h>
#include <stdarg.h>

/*************************************************
*
* vsprintf - print to a string (variable args)
*
* Inputs:
*	string - pointer to string to write to
*	fmt - format string
*	args - argument list
*
* Returns:
*	Number of characters transmitted, or
*	-1 if an error occured.
*
*************************************************/
int vsprintf(char *string,char *fmt,va_list args)
{
#ifndef _MULTI_THREAD
  return(_u_print(string,fmt,args));
#else
  return(_mt_sprint(string,fmt,args));
#endif
}
