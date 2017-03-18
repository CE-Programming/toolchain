/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>

/*************************************************
*
* _u_flt_rnd - Round to specified number of digits
*
* Inputs:
*	info - flt_info structure
*	digits - number of digits of precision
*
* Returns:
*	nothing
*
*************************************************/
void _u_flt_rnd(struct flt_info *info, char digits)
{
  register unsigned char i;
  register unsigned char carry,any;

  if (digits <= 0)
    return;

  carry = any = 0;
  for (i = MAXDIGITS-1; i >= digits; -- i) {
    carry = info->digits[i] >= 5;
    any |= info->digits[i];
    info->digits[i] = 0;
  }

  if (carry)
    ++info->digits[i];
  while (i > 0 && info->digits[i] == 10) {
    info->digits[i] = 0;
    --i;
    info->digits[i]++;
  }

  if (info->digits[0] == 10) {
    ++info->exp;
    info->digits[0] = 1;
  }
}
