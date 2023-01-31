/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI's decimal floating-point library
 */

#ifndef TI_REAL_H
#define TI_REAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* @cond */
#define tiflags __attribute__((__tiflags__))
/* @endcond */

/**
 * @brief Structure of real variable type
 */
typedef struct real_t { int8_t sign, exp; uint8_t mant[7]; } real_t;
/**
 * @brief Structure of complex variable type
 */
typedef struct cplx_t { real_t real, imag; } cplx_t;

/** OP1 Variable */
#define os_OP1                  ((uint8_t*)0xD005F8)
/** OP2 Variable */
#define os_OP2                  ((uint8_t*)0xD00603)
 /** OP3 Variable */
#define os_OP3                  ((uint8_t*)0xD0060E)
/** OP4 Variable */
#define os_OP4                  ((uint8_t*)0xD00619)
/** OP5 Variable */
#define os_OP5                  ((uint8_t*)0xD00624)
/** OP6 Variable */
#define os_OP6                  ((uint8_t*)0xD0062F)
/** OP7 Variable */
#define os_OP7                  ((uint8_t*)0xD0063A)

/**
 * Contains data used by the statistics package.
 * If you use this area, mark it invalid:
 * 
 * @code{.cpp}
 * #include <ti/vars.h>
 * // . . .
 * os_DelRes();
 * @endcode
 * 
 * Type: `uint8_t[531]`
 */
#define os_StatVars          ((uint8_t*)0xD01191)

/** @defgroup finance_reals Finance Reals
 * The following are finance variables that are always allocated.
 * They are all `real_t`.
 */
/** \addtogroup finance_reals
 *  @{
 */
#define os_Fin_N             (*(real_t*)0xD01F38)
#define os_Fin_I             (*(real_t*)0xD01F41)
#define os_Fin_PV            (*(real_t*)0xD01F4A)
#define os_Fin_PMT           (*(real_t*)0xD01F53)
#define os_Fin_FV            (*(real_t*)0xD01F5C)
#define os_Fin_PY            (*(real_t*)0xD01F65)
#define os_Fin_CY            (*(real_t*)0xD01F6E)
#define os_Cal_N             (*(real_t*)0xD01F77)
#define os_Cal_I             (*(real_t*)0xD01F80)
#define os_Cal_PV            (*(real_t*)0xD01F89)
#define os_Cal_PMT           (*(real_t*)0xD01F92)
#define os_Cal_FV            (*(real_t*)0xD01F9B)
#define os_Cal_PY            (*(real_t*)0xD01FA4)
/** @}*/

/**
 * Copies a real_t type
 *
 * @param[in] src Pointer to original real_t
 * @returns Copied real_t
 */
real_t os_RealCopy(const real_t *src);

/* Unary operations used to interact with the OS math functions */
/** Takes the arccosine of a real_t, giving the answer in radians
 *  @note Ensure -1 <= *arg <= 1, or program will crash. */
real_t os_RealAcosRad(const real_t *arg);
/** Takes the arcsine of a real_t, giving the answer in radians
 *  @note Ensure -1 <= *arg <= 1, or program will crash. */
real_t os_RealAsinRad(const real_t *arg);
/** Takes the arctangent of a real_t, giving the answers in radians */
real_t os_RealAtanRad(const real_t *arg);
/** Takes the cosine of a real_t given in radians */
real_t os_RealCosRad(const real_t *arg);
/** Converts a real_t from radians to degrees */
real_t os_RealRadToDeg(const real_t *arg);
/** Evaluates the exponential function (e^x, where e=2.717..) of a real_t */
real_t os_RealExp(const real_t *arg);
/** Takes the floor of a real_t */
real_t os_RealFloor(const real_t *arg);
/** Extracts the fractional part of a real_t */
real_t os_RealFrac(const real_t *arg);
/** Rounds a real_t to the nearest integer */
real_t os_RealRoundInt(const real_t *arg);
/** Takes the natural logarithm of a real_t
 *  @note To take log base 10, divide this value by ln(10) */
real_t os_RealLog(const real_t *arg);
/** Negates a real_t */
real_t os_RealNeg(const real_t *arg);
/** Converts a real_t from degrees to radians */
real_t os_RealDegToRad(const real_t *arg);
/** Takes the reciprocal of a real_t */
real_t os_RealInv(const real_t *arg);
/** Takes the sine of a real_t given in radians */
real_t os_RealSinRad(const real_t *arg);
/** Takes the square root of a real_t */
real_t os_RealSqrt(const real_t *arg);
/** Takes the tangent of a real_t given in radians */
real_t os_RealTanRad(const real_t *arg);
/** Extracts the integer part of a real_t */
real_t os_RealInt(const real_t *arg);
/** Calculates the square of a cplx_t */
cplx_t os_CplxSquare(const cplx_t *arg);

/* Binary operations used to interact with the OS math functions */
/** Adds two real_t values */
real_t os_RealAdd(const real_t *arg1, const real_t *arg2);
/** Divides two real_t values */
real_t os_RealDiv(const real_t *arg1, const real_t *arg2);
/** Calculates the Greatest Common Divisor of two real_t values */
real_t os_RealGcd(const real_t *arg1, const real_t *arg2);
/** Calculates the Least Common Multiple of two real_t values */
real_t os_RealLcm(const real_t *arg1, const real_t *arg2);
/** Returns the larger of two real_t values */
real_t os_RealMax(const real_t *arg1, const real_t *arg2);
/** Returns the smaller of two real_t values */
real_t os_RealMin(const real_t *arg1, const real_t *arg2);
/** Multiplies two real_t values */
real_t os_RealMul(const real_t *arg1, const real_t *arg2);
/** Calculates the value of nCr (binomial coefficient) for two real_t values */
real_t os_RealNcr(const real_t *total, const real_t *num);
/** Calculates the value of nPr (permutation number) for two real_t values */
real_t os_RealNpr(const real_t *total, const real_t *num);
/** Raises one real_t value to the power of another */
real_t os_RealPow(const real_t *base, const real_t *exp);
/** Returns a random real_t between min and max */
real_t os_RealRandInt(const real_t *min, const real_t *max);
/** Calculates the remainder (modulo) of two real_t values */
real_t os_RealMod(const real_t *arg1, const real_t *arg2);
/** Subtracts two real_t values */
real_t os_RealSub(const real_t *arg1, const real_t *arg2);

/**
 * Rounds a real_t
 *
 * @param[in] arg Real variable.
 * @param[in] digits Number of digits to round to.
 * @note digits must be in the range 0 - 9
 */
real_t os_RealRound(const real_t *arg, char digits);

/**
 * Compares two real_t
 *
 * @param[in] arg1 Real variable 1.
 * @param[in] arg2 Real variable 2.
 * @returns -1, 0, or 1 if arg1 is less than, equal to, or greater than arg2.
 * @note <tt>os_RealCompare(arg1, arg2) op 0</tt> computes <tt>arg1 op arg2</tt> for any comparison operator \c op.
 */
int os_RealCompare(const real_t *arg1, const real_t *arg2);

/**
 * Converts a real_t to an integer
 *
 * @param[in] arg Real variable.
 * @note Saturates on overflow
 */
int24_t os_RealToInt24(const real_t *arg);

/**
 * Converts an integer to a real_t
 *
 * @param arg Integer value.
 * @note Saturates on overflow
 */
tiflags real_t os_Int24ToReal(int24_t arg);

/**
 * Converts a real_t to a float
 *
 * @param arg Real variable.
 * @note Saturates on overflow
 */
float os_RealToFloat(const real_t *arg);

/**
 * Converts a float to a real_t
 *
 * @param[in] arg Float value.
 * @note Saturates on overflow
 */
real_t os_FloatToReal(float arg);

/**
 * This converts a ti-float to a ti-ascii string.
 *
 * @param[in] result Zero terminated string copied to this address
 * @param[in] arg Real to convert
 * @param[in] maxLength
 *  <=0: use default max length (14)                            <br>
 *  >0:  max length of result, minimum of 6
 * @param[in] mode:
 *  0: Use current mode for everything (digits ignored)         <br>
 *  1: Normal mode                                              <br>
 *  2: Sci mode                                                 <br>
 *  3: Eng mode                                                 <br>
 *  >4: Use current Normal/Sci/Eng mode (digits still used)     <br>
 * @param[in] digits
 *  -1:  Float mode                                             <br>
 *  0-9: Fix # mode                                             <br>
 * @returns Length of result
 */
int os_RealToStr(char *result, const real_t *arg, int8_t maxLength, uint8_t mode, int8_t digits);

/**
 *  This converts a ti-ascii string to a ti-float.
 *
 *  String format regexp: / *[-\032+]?[0-9]*(\.[0-9]*)?([eE\033][-\032+]?[0-9]*)?/
 *  @param[in] string TI-ascii string to convert
 *  @param[in] end If non-null, pointer to end of parsed number is stored here
 *  @returns resulting TI-float; on exponent overflow this is +-9.9999999999999e99
 */
real_t os_StrToReal(const char *string, char **end);

#undef tiflags

#ifdef __cplusplus
}
#endif

#endif
