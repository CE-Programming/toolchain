#if 1

/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                             Zilog, Inc.                              */
/*                                                                      */
/*                         San Jose, California                         */
/*                                                                      */
/************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <math.h>
#include <errno.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define c_isdigit(c) ((c) >= '0' && (c) <= '9')

/*************************************************
*
* strtold - string to long double conversion
*
* Inputs:
*       str - pointer to the character string
*       endptr - pointer to pointer to char to
*                put address of first char past
*                the end of the string -- or NULL
* Returns:
*       the value of the number
*
*************************************************/

/**
 * @remarks `*str >= '0' && *str <= '9'` is smaller than calls to `isdigit(*str)`
 * @todo Add support for INF INFINITY NAN NAN(...)
 */
long double strtold(char const * const __restrict nptr, char **__restrict endptr)
{
    F64_pun val;
    int frac = 0;
    int exp = 0;
    bool sign = false;
    bool exp_sign = false;
    char const *__restrict str = nptr;

    while (isspace(*str)) {
        ++str;
    }

    if (*str == '-') {
        sign = true;
        ++str;
    } else if (*str == '+') {
        ++str;
    }

    bool has_digits = false;

    val.flt = 0.0L;
    while (c_isdigit(*str)) {
        has_digits = true;
        val.flt = val.flt * 10.0L + (long double)(*str - '0');
        ++str;
    }

    if (*str == '.') {
        ++str;
        while (c_isdigit(*str)) {
            has_digits = true;
            val.flt = val.flt * 10.0L + (long double)(*str - '0');
            ++frac;
            ++str;
        }
    }

    if (!has_digits) {
        str = nptr;
        goto finish;
    }

    if (*str == 'e' || *str == 'E') {
        char const * const end_of_digits = str;
        ++str;
        if (*str == '-') {
            exp_sign = true;
            ++str;
        } else if (*str == '+') {
            ++str;
        }
        if (!c_isdigit(*str)) {
            str = end_of_digits;
            val.flt = 0.0L;
            goto finish;
        }
        while (c_isdigit(*str)) {
            exp = exp * 10 + (*str - '0');
            ++str;
        }
    }

    if (exp_sign) {
        exp = -exp;
    }
    exp -= frac;
    if (val.bin != 0)
    {
        while (exp > 0 )
        {
            val.flt *= 10.0L;
            if (!isfinite(val.flt))
            {
                errno = ERANGE;
                val.flt = HUGE_VALL;
                break;
            }
            --exp;
        }
        while (exp < 0 )
        {
            val.flt /= 10.0L;
            if (val.bin == 0)
            {
                errno = ERANGE;
                break;
            }
            ++exp;
        }
    }
    if (sign) {
        val.flt = -val.flt;
    }

finish:
    if (endptr) {
        *endptr = (char*)str;
    }

    return val.flt;
}

#else

/* unfinished routine */

#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <math.h>
#include <errno.h>

typedef union F64_pun {
    long double flt;
    uint64_t bin;
} F64_pun;

#define INF_TEXT (('i' << 0) | ('n' << 8) | ('f' << 16))
#define NAN_TEXT (('n' << 0) | ('a' << 8) | ('n' << 16))

#define Float64_pos_nan UINT64_C(0x7FF8000000000000)

long double strtold(const char *__restrict nPtr, char **__restrict endPtr) {
    const char* str = nPtr;
    while(isspace(*str)) {
        str++;
    }
    bool negative_sign = (*str == '-');
    if (*str == '+' || *str == '-') {
        str++;
    }

    // converts to lowercase via a bitwise OR
    uint24_t text_compare = *((const uint24_t*)((const void*)str)) | 0x202020;
    if (text_compare == INF_TEXT) {
        str += 3;
        *endPtr = (char*)str;
        long double ret = HUGE_VALL;
        return negative_sign ? -ret : ret;
    }
    if (text_compare == NAN_TEXT) {
        str += 3;
        *endPtr = (char*)str;
        F64_pun ret;
        ret.bin = Float64_pos_nan;
        return negative_sign ? -ret.flt : ret.flt;
    }
    while (*str == '0') {
        str++;
    }
    /* insert hexadecimal float here */
    bool u64_overflow = false;
    long double ret = 0.0L;
    {
        uint64_t int_part = 0;
        uint8_t digit_count = 0;
        while (isdigit(*str)) {
            int_part *= 10;
            int_part += *str - '0';
            str++;
            digit_count++;
            if (digit_count >= 19) {
                // 9'999'999'999'999'999'999
                u64_overflow = true;
                break;
            }
        }
        ret = (long double)int_part;
    }
    if (u64_overflow) {
        /**
         * we already read at least 59.7 bits of precision, which is more
         * than enough for rounding purposes. Skip the rest of the digits.
         */
        while (isdigit(*str)) {
            #if 0
                #ifdef FP_FAST_FMAL
                    ret = fmal(ret, 10.0L, (long double)(*str - '0'));
                #else
                    ret *= 10.0L;
                    ret += (long double)(*str - '0');
                #endif
            #else
                ret *= 10.0L;
            #endif
            str++;
        }
        if (!isfinite(ret)) {
            long double ret = HUGE_VALL;
        }
        if (*str == '.') {
            str++;
        }
        while (isdigit(*str)) {
            str++;
        }
    } else if (*str == '.') {
        str++;
        uint64_t frac_part = 0;
        bool decimal_overflow = false;
        uint8_t digit_count = 0;
        while (isdigit(*str)) {
            frac_part *= 10;
            frac_part += *str - '0';
            str++;
            digit_count++;
            if (digit_count >= 19) {
                // 9'999'999'999'999'999'999
                decimal_overflow = true;
                break;
            }
        }
        long double decimal_part = (long double)frac_part;
        while (digit_count --> 0) {
            decimal_part /= 10.0L;
        }
        if (decimal_overflow) {
            while (isdigit(*str)) {
                str++;
            }
        }
    }
    if (*str == 'E' || *str == 'e') {
        bool expon_sign = false;
        if (*str == '-') {
            expon_sign = true;
        }
        if (*str == '+' || *str == '-') {
            str++;
        }
        while (*str == '0') {
            str++;
        }
        uint24_t expon = 0;
        expon += *str - '0'; str++;
        if (isdigit(*str)) {
            expon *= 10;
            expon += *str - '0'; str++;
        }
        if (isdigit(*str)) {
            expon *= 10;
            expon += *str - '0'; str++;
        }
        // LDBL_MAX / LDBL_TRUE_MIN == around 10^630
        if (isdigit(*str)) {
            ret = expon_sign ? 0.0L : HUGE_VALL;
            goto final_ret;
        }
    }
    final_ret:
    *endPtr = (char*)str;
    return negative_sign ? -ret : ret;
}

#endif
