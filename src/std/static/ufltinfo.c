/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <stddef.h>
#include <format.h>
#include <string.h>

#define BIT_PACKING 1
#if (BIT_PACKING == 1)
typedef union
{
  float f;
  struct {
    unsigned long sign:1,
      exponent:8,
      mantissa:23;
  } s;
  long l;
} ieee_795_float;
#define EXP(e) (e)
#else
typedef union {
  float f;
  unsigned long l;
  struct {
   unsigned int exponent1:1;
   unsigned int mantissa:23;
   unsigned int dummy:16;
   unsigned int sign:1, exponent2:7;
  } s;
}ieee_795_float;
#define EXP(e) ((e##2 << 1) | (e##1))
#endif


typedef long reg_t;
typedef unsigned long ureg_t;
/*************************************************
*
* _u_flt_info - Fills flt_info structure
*
* Inputs:
*	val - value to be converted
*	info - flt_info structure to be filled in.
*
* Outputs:
*	info->sign - TRUE if val is negative; FALSE otherwise.
*	info->exp - The power of ten in scientific notation.
*	info->digits[] - The first digit is the ones place, the rest are
*	decimal digits.
*
* Returns:
*	nothing
*
* Notes:
* 	I moved the rounding out to the calling routine (which does it
*	anyway).  As a space optimization, we compute all the digits out
*	to MAXDIGITS, so we no longer pay attention to ndig.<THH>
*	This only works for floating-point numbers having the format as
*	specified in the above structure.
* Algorithm:
*	Too much precision is lost working in the floating-point domain, so we
*	unpack the fields of the floating-point number, force the base-2
*	exponent to zero and then convert the normalized mantissa to decimal
*	digits.
*************************************************/
void _u_flt_info(double val,struct flt_info * info)
{
  ieee_795_float rep;
  register reg_t exp;		// The base-2 exponent as a signed value.
  register reg_t exp10 = 0;	// The base-10 exponent.
  register ureg_t mant;	// The mantissa, as an unsigned value.
  register ureg_t i;

  // Clear the info structure (represents +0.000000000).
  memset(info,0,sizeof(struct flt_info));

  rep.f = val;

  // All zero means zero!
  if (rep.l == 0) return;

  if (rep.s.sign)
    info->flags = FLT_INFO_SIGN;

  // OK, unpack some fields.

  exp = EXP(rep.s.exponent);

  mant = rep.s.mantissa;

  // If the exponent is 0xff, it is a special representation (Inf or NaN).
  if (exp == 0xff)
  {
    // If the mantissa is zero, it's Inf; otherwise, NaN.
    if (rep.s.mantissa == 0)
      info->flags |= FLT_INFO_INF;
    else
      info->flags |= FLT_INFO_NAN;
    return;
  }

  // If the exponent is zero, this is a denormalized number.
  if (exp != 0)
  {
    mant |= 0x800000uL;	// Or in the implicit bit.
    --exp;		// And decrement the exponent.
    // (denormalized numbers are offset 126, not offset 127.
    // In the assembly realm, we could handle this in one step by shifting the 1
    // into the msb of a left-adjusted 23-bit mantissa.
  }

  // Now, we have something that looks like
  //	0000 0000 x.xxx xxxx xxxx xxxx xxxx xxxx
  // in mant, and the binary exponent -- offset by +126 -- in exp.
  //
  // Now, we want to shift the mantissa left so we leave a few guard bits at the
  // right end of the word, but we also want to leave four bits to the left of
  // the decimal point so we can pick off the decimal digits later.
  //
  // If we move the decimal point from where it is to the right end of the first
  // nibble, we essentially subtract 5 bits from the offset.  But shifting the
  // mantissa left by the same number of bits cancels the difference.
  // Let's do the shift and subtract the remaining offset.
  mant <<= 5;
  exp -= 126;

  // Now the picture is
  //	000x.xxxx xxxx xxxx xxxx xxxx xxx0 0000

  // We want to drive the base-2 exponent to zero, and accumulate multiplication
  // or division by 10 in the base-10 exponent.
  // We start by decrementing the exponent while shifting the bits in the
  // mantissa left by 1 each time.  This changes the representation, but not its
  // value.
  // If the msb becomes true, a shift would cause us to lose information, so in
  // that case, we divide the mantissa by 10 and increment the base-10
  // exponent.  Once again, this changes the bits in the representation, but not
  // the value that is represented -- at least not very much.  Division by 10
  // may cause bits to fall of the end of the 32-bit word, and some precision is
  // lost.  But we always have a whole nibble, plus about 2/3 of a bit as guard
  // bits.


// At most one of the following while loops will execute.

  // If the base-2 exponent is positive, this while loop drives it to zero by
  // repeatedly shifting the mantissa left by one bit and decrementing the exponent.
  // This changes the representation, but leaves unchanged the value
  // it represents.
  while (exp > 0)
  {
    if ((mant >> 27) > 9)
    {
      // If a left shift would cause something greater than 9 to appear in the
      // first nibble, normalize right.
      mant /= 5;
      ++exp10;
    }
    else
      mant <<= 1;
    // Dividing by 5 and adding one to the base-10 exponent is the same as
    // shifting left by one bit: They both multiply the representation by two.
    // Decrementing the base-2 exponent leaves the entire representation unchanged.
    --exp;
  }

  // If the base-2 exponent is negative, this while loop drives it to zero by
  // repeatedly shifting the mantissa right by one bit and incrementing the exponent.
  while (exp < 0)
  {
    if ((mant >> 28) < 2)
    {
      // If a right shift would cause the first nibble to go to zero, normalize left.
      mant *= 5;
      --exp10;
    }
    else
      mant >>= 1;
    // Multiplying by 5 and subtracting one from the base-10 exponent is the
    // same as shifting right by one bit: They both divide the representation by 2.
    // Incrementing the base-2 exponent leaves the entire representation unchanged.
    ++exp;
  }

  // Now, that we have driven the base-2 exponent to zero, the base-10 exponent
  // is ready.
  info->exp = exp10;

  // Finally, we can pick off the digits.
  // This is done by picking off the first nibble (which must be a decimal digit
  // between 1 and 9 inclusive) and then multiplying the remaining 28 bits by
  // 10.  That leaves another decimal digit (in [0,9]) in the top nibble, so we
  // just loop for as many digits as we want.
  for (i=0; i < MAXDIGITS; ++i)
  {
    info->digits[i] = mant >> 28;
    mant &= 0xfffffffuL;
    mant *= 10;
  }

  /* Rounding moved out to callers of _u_flt_info(). */
}
