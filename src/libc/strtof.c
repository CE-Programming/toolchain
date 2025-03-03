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

typedef union F32_pun {
    float flt;
    uint32_t bin;
} F32_pun;

/*************************************************
*
* strtof - string to float conversion
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
float _strtof_c(const char *__restrict nptr, char **__restrict endptr)
{
    F32_pun val;
    int frac = 0;
    int exp = 0;
    bool sign = false;
    bool exp_sign = false;
    char *str = (char*)nptr;

    while (isspace(*str)) {
        ++str;
    }

    if (*str == '-') {
        sign = true;
        ++str;
    } else if (*str == '+') {
        ++str;
    }

    val.flt = 0.0f;

    while (*str >= '0' && *str <= '9') {
        val.flt = val.flt * 10.0f + (float)(*str - '0');
        ++str;
    }

    if (*str == '.') {
        ++str;
        while (*str >= '0' && *str <= '9') {
            val.flt = val.flt * 10.0f + (float)(*str - '0');
            ++frac;
            ++str;
        }
    }

    if (*str == 'e' || *str == 'E') {
        ++str;
        if (*str == '-') {
            exp_sign = true;
            ++str;
        } else if (*str == '+') {
            exp_sign = false;
            ++str;
        }
        while (*str >= '0' && *str <= '9') {
            exp = exp * 10 + (*str - '0');
            ++str;
        }
    }

    if (endptr) {
        *endptr = (char*)str;
    }

    if (exp_sign) {
        exp = -exp;
    }
    exp -= frac;
    if (val.bin != 0)
    {
        while (exp > 0 )
        {
            val.flt *= 10.0f;
            if (!isfinite(val.flt))
            {
                errno = ERANGE;
                val.flt = HUGE_VALF;
                break;
            }
            --exp;
        }
        while (exp < 0 )
        {
            val.flt /= 10.0f;
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
    return val.flt;
}

double _strtod_c(const char *, char **) __attribute__((alias("_strtof_c")));
