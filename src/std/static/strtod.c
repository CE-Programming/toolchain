/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <math.h>
#include <errno.h>
//#include <float.h>


/*************************************************
*
* strtod - string to double conversion
*
* Inputs:
*	str - pointer to the character string
*	endptr - pointer to pointer to char to
*		 put address of first char past
*		 the end of the string -- or NULL
* Returns:
*	the value of the number
*
*************************************************/
double strtod(char * str,char ** endptr)
{
  union
  {
    double d;
    unsigned short s[2];
  }val;
  int frac = 0;
  int exp = 0;
  signed char sign = 1;
  signed char exp_sign = 1;

  while (isspace(*str))
    ++str;

  if (*str == '-') {
    sign = -1;
    ++str;
  }
  else if (*str == '+')
    ++str;

  val.d = 0;
  while (*str >= '0' && *str <= '9') {
    val.d = val.d * 10 + (*str - '0');
    ++str;
  }

  if (*str == '.') {
    ++str;
    while (*str >= '0' && *str <= '9') {
      val.d = val.d * 10 + (*str - '0');
      ++frac;
      ++str;
    }
  }

  if (*str == 'e' || *str == 'E') {
    ++str;
    if (*str == '-') {
      exp_sign = -1;
      ++str;
    }
    else if (*str == '+') {
      exp_sign = 1;
      ++str;
    }
    while (*str >= '0' && *str <= '9') {
     exp = exp * 10 + (*str - '0');
      ++str;
    }
  }

  if (endptr)
    *endptr = str;

  if (exp_sign < 0 )
     exp = -exp;
  exp -= frac;
  if (val.d != 0)
  {
    while (exp > 0 )
    {
       val.d  *= 10.0;
       if (val.s[1] == 0x7f80)
       {
         errno = ERANGE;
         val.d = HUGE_VAL;
         break;
       }
       --exp;
    }
    while (exp < 0 )
    {
       val.d  *= .1;
       if (val.s[1] == 0)
       {
         errno = ERANGE;
         break;
       }
       ++exp;
    }
    if (sign < 0 )
       val.s[1] |= 0x8000;
  }
  return val.d;
}
