/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <string.h>
#include <format.h>

/*************************************************
*
* _u_reverse - reverse a string leaving the end
*	       of string indicator at the end
*	       of the string
*
* Inputs:
*	str - string to be reversed
*
* Returns:
*	str - string reversed
*
*************************************************/
void _u_reverse(char *s)
{
  register char *ss = s;
  register size_t len = strlen(s);
  register char *pp = s + len - 1;
  register char c;

  while (len > 1) {
    c = *pp;
    *pp-- = *ss;
    *ss++ = c;
    len -= 2;
  }
}
