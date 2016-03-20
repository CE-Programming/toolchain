/*************************************************
 *  Copyright (C) 2006-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>

/*************************************************
*
* strtoul - string to unsigned long conversion
*
* Inputs:
*	cp - pointer to the character string
*	endptr - place to put ptr to first invalid character
*	base - radix
*
* Returns:
*	the value of the number
*
*************************************************/
unsigned long strtoul(char * cp,char ** endptr,int base)
{
  register unsigned long sum,psum;
  register unsigned char sign;
  register unsigned char radix = base;
  register unsigned char digit;

  while (isspace(*cp))
    ++cp;

  sign = 0;
  
  if ( *cp == '+' ) {
    ++cp;
  }
  else if ( *cp == '-' ) {
    ++cp;
    sign = 1;
  }

  if (base == 0) {
    if (*cp == '0')
      if (cp[1] == 'x' || cp[1] == 'X')
	radix = 16;
      else
	radix = 8;
    else
      radix = 10;
  }

  /* If the base is declared as 16, the "0x" prefix may be ignored. */
  if (base == 16 && *cp == '0' && (cp[1] == 'x' || cp[1] == 'X'))
    cp += 2;

  sum = 0;
  for (;;) {
    digit = toupper(*(cp++));	 
    if (digit >= 'A')
      digit = digit - ('A' - 10);
    else
      digit -= '0';
    if (digit >= radix)
      break;
    psum = sum;
    sum = sum * radix + digit;
    if (sum < psum) {	/* overflow */
      errno = ERANGE; 
      sum = ULONG_MAX;
    }
  }

  if (sign) {
 //   errno = ERANGE;
 //   sum = 0;
      sum = -sum;
  }

  if (endptr) {
    --cp;
    if (base == 0) {
      while (*cp == 'h' || *cp == 'u' ||
	     *cp == 'l' || *cp == 'L')
	++cp;
    }
    *endptr = (char*)cp;
  }
  return(sum);
}
