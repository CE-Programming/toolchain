#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <ti/sprintf.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

#define C(expr) if (!(expr)) { return __LINE__; }

#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#define TEST_NAME(test, name) { ret = test; if (ret != 0) { puts(name); return ret; }}

#define NO_ERR 0

//------------------------------------------------------------------------------
// Internal functions
//------------------------------------------------------------------------------

int __strtoi(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

unsigned int __strtoui(const char *__restrict nptr, char **__restrict endptr, int base) __attribute__((nonnull(1)));

//------------------------------------------------------------------------------
// Char to digit
//------------------------------------------------------------------------------

/**
 * returns [0, 9] when ['0', '9']
 * returns [10, 35] when ['A', 'Z'] or ['a', 'z']
 * otherwise returns -1
 */
char char_to_digit(char c);

char char_to_digit_truth(char c) {
    if (c >= '0' && c <= '9') {
        return (c - '0');
    }
    if (c >= 'A' && c <= 'Z') {
        return (c - 'A') + 10;
    }
    if (c >= 'a' && c <= 'z') {
        return (c - 'a') + 10;
    }
    return -1;
}

int test_char_to_digit(void) {
    for (int i = 0x00; i <= 0xFF; i++) {
        char c = (char)i;
        char guess = char_to_digit(c);
        char truth = char_to_digit_truth(c);
        if (guess != truth) {
            test_printf("%02X: %d != %d\n", (uint8_t)c, guess, truth);
            return __LINE__;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
// atoint tests
//------------------------------------------------------------------------------

typedef long long (*atoint_func)(const char* nptr);

long long atoint_atoi(const char* nptr) {
    return (long long)atoi(nptr);
}

long long atoint_atol(const char* nptr) {
    return (long long)atol(nptr);
}

long long atoint_atoll(const char* nptr) {
    return (long long)atoll(nptr);
}

long long atoint_strtoi(const char* nptr) {
    return (long long)__strtoi(nptr, NULL, 10);
}

long long atoint_strtoui(const char* nptr) {
    return (long long)((int)__strtoui(nptr, NULL, 10));
}

long long atoint_strtol(const char* nptr) {
    return (long long)strtol(nptr, NULL, 10);
}

long long atoint_strtoul(const char* nptr) {
    return (long long)((long)strtoul(nptr, NULL, 10));
}

long long atoint_strtoll(const char* nptr) {
    return strtoll(nptr, NULL, 10);
}

long long atoint_strtoull(const char* nptr) {
    return (long long)strtoull(nptr, NULL, 10);
}

bool atoint_verify(atoint_func func, long long truth, const char* nptr) {
    long long guess = (func)(nptr);
    if (guess == truth) {
        return true;
    }
    test_printf("E: %llX\n", guess);
    return false;
}

int atoint_test(atoint_func const func) {
    C(atoint_verify(func,      0, ""             ));
    C(atoint_verify(func,      0, "+"            ));
    C(atoint_verify(func,      0, "-"            ));
    C(atoint_verify(func,      0, "0"            ));
    C(atoint_verify(func,      0, "+0"           ));
    C(atoint_verify(func,      0, "-0"           ));
    C(atoint_verify(func,      1, "1"            ));
    C(atoint_verify(func,      1, "+1"           ));
    C(atoint_verify(func,     -1, "-1"           ));
    C(atoint_verify(func,      0, "+-84"         ));
    C(atoint_verify(func,      0, "--84"         ));
    C(atoint_verify(func,      0, "-+84"         ));
    C(atoint_verify(func,      0, "++84"         ));
    C(atoint_verify(func,      0, "+ 84"         ));
    C(atoint_verify(func,      0, "- 84"         ));
    C(atoint_verify(func,  10000, "10000"        ));
    C(atoint_verify(func,  10000, "+10000"       ));
    C(atoint_verify(func, -10000, "-10000"       ));
    C(atoint_verify(func,   -123, " -123junk"    ));
    C(atoint_verify(func,    321, " +321dust"    ));
    C(atoint_verify(func,     99, " \f\n\r\t\v99"));
    C(atoint_verify(func,     42, "0042"         ));
    C(atoint_verify(func,      0, "0x2A"         ));
    C(atoint_verify(func,      0, "junk"         ));
    C(atoint_verify(func,      0, "a701"         ));
    C(atoint_verify(func,      8, "000000008"    ));
    return 0;
}

//------------------------------------------------------------------------------
// strtoint tests
//------------------------------------------------------------------------------

typedef long long (*strtoint_func)(const char* nptr, char** endptr, int base);

long long strtoint_strtoi(const char* nptr, char** endptr, int base) {
    return (long long)__strtoi(nptr, endptr, base);
}

long long strtoint_strtoui(const char* nptr, char** endptr, int base) {
    return (long long)((int)__strtoui(nptr, endptr, base));
}

long long strtoint_strtol(const char* nptr, char** endptr, int base) {
    return (long long)strtol(nptr, endptr, base);
}

long long strtoint_strtoul(const char* nptr, char** endptr, int base) {
    return (long long)((long)strtoul(nptr, endptr, base));
}

long long strtoint_strtoll(const char* nptr, char** endptr, int base) {
    return strtoll(nptr, endptr, base);
}

long long strtoint_strtoull(const char* nptr, char** endptr, int base) {
    return (long long)strtoull(nptr, endptr, base);
}

bool strtoint_verify(
    long long truth,
    const char* nptr,
    int endptr_offset,
    strtoint_func func,
    int base,
    int errno_state
) {
    char* endptr;
    long long guess;
    errno = 0;
    guess = (func)(nptr, &endptr, base);
    if (guess != truth) {
        test_printf("E: %llX\n", guess);
        return false;
    }
    if (endptr != nptr + endptr_offset) {
        test_printf("%p - %p = %td\n", endptr, nptr, endptr - nptr);
        return false;
    }
    if (errno != errno_state) {
        test_printf("errno: G %d != T %d\n", errno, errno_state);
        return false;
    }
    guess = (func)(nptr, NULL, base);
    if (guess != truth) {
        test_printf("NULL error: %llX\n", guess);
        return false;
    }
    return true;
}

int strtoint_test(strtoint_func const func) {
    /* test base 10 */
    C(strtoint_verify(      0, ""             , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "+"            , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "-"            , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "0"            , 1, func, 10, NO_ERR));
    C(strtoint_verify(      0, "+0"           , 2, func, 10, NO_ERR));
    C(strtoint_verify(      0, "-0"           , 2, func, 10, NO_ERR));
    C(strtoint_verify(      1, "1"            , 1, func, 10, NO_ERR));
    C(strtoint_verify(      1, "+1"           , 2, func, 10, NO_ERR));
    C(strtoint_verify(     -1, "-1"           , 2, func, 10, NO_ERR));
    C(strtoint_verify(      0, "+-84"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "--84"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "-+84"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "++84"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "+ 84"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "- 84"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(  10000, "10000"        , 5, func, 10, NO_ERR));
    C(strtoint_verify(  10000, "+10000"       , 6, func, 10, NO_ERR));
    C(strtoint_verify( -10000, "-10000"       , 6, func, 10, NO_ERR));
    C(strtoint_verify(   -123, " -123junk"    , 5, func, 10, NO_ERR));
    C(strtoint_verify(    321, " +321dust"    , 5, func, 10, NO_ERR));
    C(strtoint_verify(     99, " \f\n\r\t\v99", 8, func, 10, NO_ERR));
    C(strtoint_verify(     42, "0042"         , 4, func, 10, NO_ERR));
    C(strtoint_verify(      0, "0x2A"         , 1, func, 10, NO_ERR));
    C(strtoint_verify(      0, "junk"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      0, "a701"         , 0, func, 10, NO_ERR));
    C(strtoint_verify(      8, "000000008"    , 9, func, 10, NO_ERR));

    /* test other bases */
    C(strtoint_verify(          10, "1010"        ,  4, func,  2, NO_ERR));
    C(strtoint_verify(          10, "12"          ,  2, func,  8, NO_ERR));
    C(strtoint_verify(          10, "A"           ,  1, func, 16, NO_ERR));
    C(strtoint_verify(           0, "junk"        ,  0, func,  0, NO_ERR));
    C(strtoint_verify(      926192, "junk"        ,  4, func, 36, NO_ERR));
    C(strtoint_verify(     -926192, "-JuNk"       ,  5, func, 36, NO_ERR));
    C(strtoint_verify(          10, "012"         ,  3, func,  0, NO_ERR));
    C(strtoint_verify(          10, "\f0xA"       ,  4, func,  0, NO_ERR));
    C(strtoint_verify(         -83, "-0123ABC"    ,  5, func,  0, NO_ERR));
    C(strtoint_verify(      0xCAFE, "0XCAFE"      ,  6, func,  0, NO_ERR));
    C(strtoint_verify(0b1011100010, "0b1011100010", 12, func,  2, NO_ERR));
    C(strtoint_verify(0b0100011101, "0B0100011101", 12, func,  0, NO_ERR));
    C(strtoint_verify(           0, "000000000000", 12, func,  0, NO_ERR));

    /* test base 1 */
    C(strtoint_verify(           0, "\n000?"      ,  4, func,  1, NO_ERR));
    C(strtoint_verify(           0, "\t111"       ,  0, func,  1, NO_ERR));

    /* test invalid bases */
    C(strtoint_verify(           0, "\f12"       ,  0, func,      37, NO_ERR));
    C(strtoint_verify(           0, "\v34"       ,  0, func,      -1, NO_ERR));
    C(strtoint_verify(           0, "\r56"       ,  0, func, INT_MAX, NO_ERR));
    C(strtoint_verify(           0, "\t78"       ,  0, func, INT_MIN, NO_ERR));

    /**
     * @remarks If the first digit is '0' and the base is 0, then the
     * string should be treated as octal. This also implies that the string
     * contains a number, even if there are no more digits after the '0'.
     * Here we test that the string has been correctly classified as
     * containing a number, meaning that nptr != endptr.
     */
    C(strtoint_verify(           0, "0"      , 1, func,  0, NO_ERR));
    C(strtoint_verify(           0, "\n09"   , 2, func,  0, NO_ERR));

    /**
     * @remarks Make sure endptr is handled correctly when there is a
     * prefix without digits.
     */
    C(strtoint_verify(           0, "0x"   , 0, func,  0, NO_ERR));
    C(strtoint_verify(           0, "0x"   , 0, func, 16, NO_ERR));
    C(strtoint_verify(           0, "\v-0b", 0, func,  0, NO_ERR));
    C(strtoint_verify(           0, "\v-0b", 0, func,  2, NO_ERR));

    return 0;
}

//------------------------------------------------------------------------------
// Specific tests
//------------------------------------------------------------------------------

int test_atoi(void) {
    atoint_func func = atoint_atoi;
    C(atoint_verify(func,  INT_MIN, "-8388608"));
    C(atoint_verify(func,  INT_MAX, "8388607" ));
    C(atoint_verify(func,  INT_MAX, "+8388607"));
    C(atoint_verify(func, -INT_MAX, "-8388607"));
    return 0;
}

int test_atol(void) {
    atoint_func func = atoint_atol;
    C(atoint_verify(func,  LONG_MIN, "-2147483648"));
    C(atoint_verify(func,  LONG_MAX, "2147483647" ));
    C(atoint_verify(func,  LONG_MAX, "+2147483647"));
    C(atoint_verify(func, -LONG_MAX, "-2147483647"));
    return 0;
}

int test_atoll(void) {
    atoint_func func = atoint_atoll;
    C(atoint_verify(func,  LLONG_MIN, "-9223372036854775808"));
    C(atoint_verify(func,  LLONG_MAX, "9223372036854775807" ));
    C(atoint_verify(func,  LLONG_MAX, "+9223372036854775807"));
    C(atoint_verify(func, -LLONG_MAX, "-9223372036854775807"));
    return 0;
}

int test_strtoi(void) {
    strtoint_func func = strtoint_strtoi;

    C(strtoint_verify( INT_MIN, "-8388608", 8, func, 10, NO_ERR));
    C(strtoint_verify( INT_MAX, "8388608" , 7, func, 10, ERANGE));
    C(strtoint_verify( INT_MAX, "8388607" , 7, func, 10, NO_ERR));
    C(strtoint_verify( INT_MAX, "+8388607", 8, func, 10, NO_ERR));
    C(strtoint_verify(-INT_MAX, "-8388607", 8, func, 10, NO_ERR));

    C(strtoint_verify( INT_MIN, "-16777216", 9, func, 10, ERANGE));
    C(strtoint_verify( INT_MAX, "16777216" , 8, func, 10, ERANGE));
    C(strtoint_verify( INT_MAX, "16777215" , 8, func, 10, ERANGE));
    C(strtoint_verify( INT_MAX, "+16777215", 9, func, 10, ERANGE));
    C(strtoint_verify( INT_MIN, "-16777215", 9, func, 10, ERANGE));

    C(strtoint_verify( INT_MIN, "-100000000000000000000000", 25, func, 2, NO_ERR));
    C(strtoint_verify( INT_MAX, " 100000000000000000000000", 25, func, 2, ERANGE));
    C(strtoint_verify( INT_MAX, "0b11111111111111111111111", 25, func, 0, NO_ERR));
    C(strtoint_verify(-INT_MAX, " -11111111111111111111111", 25, func, 2, NO_ERR));

    C(strtoint_verify( INT_MIN, "-1000000000000000000000000", 26, func, 2, ERANGE));
    C(strtoint_verify( INT_MAX, " 1000000000000000000000000", 26, func, 2, ERANGE));
    C(strtoint_verify( INT_MAX, "0b111111111111111111111111", 26, func, 0, ERANGE));
    C(strtoint_verify( INT_MIN, " -111111111111111111111111", 26, func, 2, ERANGE));

    C(strtoint_verify( INT_MIN, "-1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));
    C(strtoint_verify( INT_MAX, "+1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));

    return 0;
}

int test_strtoui(void) {
    strtoint_func func = strtoint_strtoui;

    C(strtoint_verify( INT_MIN, "-8388608", 8, func, 10, NO_ERR));
    C(strtoint_verify( INT_MIN, "8388608" , 7, func, 10, NO_ERR));
    C(strtoint_verify( INT_MAX, "8388607" , 7, func, 10, NO_ERR));
    C(strtoint_verify( INT_MAX, "+8388607", 8, func, 10, NO_ERR));
    C(strtoint_verify(-INT_MAX, "-8388607", 8, func, 10, NO_ERR));

    C(strtoint_verify(       -1, "-16777216", 9, func, 10, ERANGE));
    C(strtoint_verify(       -1, "16777216" , 8, func, 10, ERANGE));
    C(strtoint_verify(       -1, "16777215" , 8, func, 10, NO_ERR));
    C(strtoint_verify(       -1, "+16777215", 9, func, 10, NO_ERR));
    C(strtoint_verify(        1, "-16777215", 9, func, 10, NO_ERR));

    C(strtoint_verify( INT_MIN, "-100000000000000000000000", 25, func, 2, NO_ERR));
    C(strtoint_verify( INT_MIN, " 100000000000000000000000", 25, func, 2, NO_ERR));
    C(strtoint_verify( INT_MAX, "0b11111111111111111111111", 25, func, 0, NO_ERR));
    C(strtoint_verify(-INT_MAX, " -11111111111111111111111", 25, func, 2, NO_ERR));

    C(strtoint_verify(       -1, "-1000000000000000000000000", 26, func, 2, ERANGE));
    C(strtoint_verify(       -1, " 1000000000000000000000000", 26, func, 2, ERANGE));
    C(strtoint_verify(       -1, "0b111111111111111111111111", 26, func, 0, NO_ERR));
    C(strtoint_verify(        1, " -111111111111111111111111", 26, func, 2, NO_ERR));

    C(strtoint_verify(       -1, "-1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));
    C(strtoint_verify(       -1, "+1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));

    return 0;
}

int test_strtol(void) {
    strtoint_func func = strtoint_strtol;

    C(strtoint_verify( LONG_MIN, "-2147483648", 11, func, 10, NO_ERR));
    C(strtoint_verify( LONG_MAX, "2147483648" , 10, func, 10, ERANGE));
    C(strtoint_verify( LONG_MAX, "2147483647" , 10, func, 10, NO_ERR));
    C(strtoint_verify( LONG_MAX, "+2147483647", 11, func, 10, NO_ERR));
    C(strtoint_verify(-LONG_MAX, "-2147483647", 11, func, 10, NO_ERR));

    C(strtoint_verify( LONG_MIN, "-4294967296", 11, func, 10, ERANGE));
    C(strtoint_verify( LONG_MAX, "4294967296" , 10, func, 10, ERANGE));
    C(strtoint_verify( LONG_MAX, "4294967295" , 10, func, 10, ERANGE));
    C(strtoint_verify( LONG_MAX, "+4294967295", 11, func, 10, ERANGE));
    C(strtoint_verify( LONG_MIN, "-4294967295", 11, func, 10, ERANGE));

    C(strtoint_verify( LONG_MIN, "-10000000000000000000000000000000", 33, func, 2, NO_ERR));
    C(strtoint_verify( LONG_MAX, " 10000000000000000000000000000000", 33, func, 2, ERANGE));
    C(strtoint_verify( LONG_MAX, "0b1111111111111111111111111111111", 33, func, 0, NO_ERR));
    C(strtoint_verify(-LONG_MAX, " -1111111111111111111111111111111", 33, func, 2, NO_ERR));

    C(strtoint_verify( LONG_MIN, "-100000000000000000000000000000000", 34, func, 2, ERANGE));
    C(strtoint_verify( LONG_MAX, " 100000000000000000000000000000000", 34, func, 2, ERANGE));
    C(strtoint_verify( LONG_MAX, "0b11111111111111111111111111111111", 34, func, 0, ERANGE));
    C(strtoint_verify( LONG_MIN, " -11111111111111111111111111111111", 34, func, 2, ERANGE));

    C(strtoint_verify( LONG_MIN, "-1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));
    C(strtoint_verify( LONG_MAX, "+1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));

    return 0;
}

int test_strtoul(void) {
    strtoint_func func = strtoint_strtoul;

    C(strtoint_verify( LONG_MIN, "-2147483648", 11, func, 10, NO_ERR));
    C(strtoint_verify( LONG_MIN, "2147483648" , 10, func, 10, NO_ERR));
    C(strtoint_verify( LONG_MAX, "2147483647" , 10, func, 10, NO_ERR));
    C(strtoint_verify( LONG_MAX, "+2147483647", 11, func, 10, NO_ERR));
    C(strtoint_verify(-LONG_MAX, "-2147483647", 11, func, 10, NO_ERR));

    C(strtoint_verify(       -1, "-4294967296", 11, func, 10, ERANGE));
    C(strtoint_verify(       -1, "4294967296" , 10, func, 10, ERANGE));
    C(strtoint_verify(       -1, "4294967295" , 10, func, 10, NO_ERR));
    C(strtoint_verify(       -1, "+4294967295", 11, func, 10, NO_ERR));
    C(strtoint_verify(        1, "-4294967295", 11, func, 10, NO_ERR));

    C(strtoint_verify( LONG_MIN, "-10000000000000000000000000000000", 33, func, 2, NO_ERR));
    C(strtoint_verify( LONG_MIN, " 10000000000000000000000000000000", 33, func, 2, NO_ERR));
    C(strtoint_verify( LONG_MAX, "0b1111111111111111111111111111111", 33, func, 0, NO_ERR));
    C(strtoint_verify(-LONG_MAX, " -1111111111111111111111111111111", 33, func, 2, NO_ERR));

    C(strtoint_verify(       -1, "-100000000000000000000000000000000", 34, func, 2, ERANGE));
    C(strtoint_verify(       -1, " 100000000000000000000000000000000", 34, func, 2, ERANGE));
    C(strtoint_verify(       -1, "0b11111111111111111111111111111111", 34, func, 0, NO_ERR));
    C(strtoint_verify(        1, " -11111111111111111111111111111111", 34, func, 2, NO_ERR));

    C(strtoint_verify(       -1, "-1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));
    C(strtoint_verify(       -1, "+1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));

    return 0;
}

int test_strtoll(void) {
    strtoint_func func = strtoint_strtoll;

    C(strtoint_verify( LLONG_MIN, "-9223372036854775808", 20, func, 10, NO_ERR));
    C(strtoint_verify( LLONG_MAX, "9223372036854775808" , 19, func, 10, ERANGE));
    C(strtoint_verify( LLONG_MAX, "9223372036854775807" , 19, func, 10, NO_ERR));
    C(strtoint_verify( LLONG_MAX, "+9223372036854775807", 20, func, 10, NO_ERR));
    C(strtoint_verify(-LLONG_MAX, "-9223372036854775807", 20, func, 10, NO_ERR));

    C(strtoint_verify( LLONG_MIN, "-18446744073709551616", 21, func, 10, ERANGE));
    C(strtoint_verify( LLONG_MAX, "18446744073709551616" , 20, func, 10, ERANGE));
    C(strtoint_verify( LLONG_MAX, "18446744073709551615" , 20, func, 10, ERANGE));
    C(strtoint_verify( LLONG_MAX, "+18446744073709551615", 21, func, 10, ERANGE));
    C(strtoint_verify( LLONG_MIN, "-18446744073709551615", 21, func, 10, ERANGE));

    C(strtoint_verify( LLONG_MIN, "-1000000000000000000000000000000000000000000000000000000000000000", 65, func, 2, NO_ERR));
    C(strtoint_verify( LLONG_MAX, " 1000000000000000000000000000000000000000000000000000000000000000", 65, func, 2, ERANGE));
    C(strtoint_verify( LLONG_MAX, "0b111111111111111111111111111111111111111111111111111111111111111", 65, func, 0, NO_ERR));
    C(strtoint_verify(-LLONG_MAX, " -111111111111111111111111111111111111111111111111111111111111111", 65, func, 2, NO_ERR));

    C(strtoint_verify( LLONG_MIN, "-10000000000000000000000000000000000000000000000000000000000000000", 66, func, 2, ERANGE));
    C(strtoint_verify( LLONG_MAX, " 10000000000000000000000000000000000000000000000000000000000000000", 66, func, 2, ERANGE));
    C(strtoint_verify( LLONG_MAX, "0b1111111111111111111111111111111111111111111111111111111111111111", 66, func, 0, ERANGE));
    C(strtoint_verify( LLONG_MIN, " -1111111111111111111111111111111111111111111111111111111111111111", 66, func, 2, ERANGE));

    C(strtoint_verify( LLONG_MIN, "-1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));
    C(strtoint_verify( LLONG_MAX, "+1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));

    return 0;
}

int test_strtoull(void) {
    strtoint_func func = strtoint_strtoull;

    C(strtoint_verify( LLONG_MIN, "-9223372036854775808", 20, func, 10, NO_ERR));
    C(strtoint_verify( LLONG_MIN, "9223372036854775808" , 19, func, 10, NO_ERR));
    C(strtoint_verify( LLONG_MAX, "9223372036854775807" , 19, func, 10, NO_ERR));
    C(strtoint_verify( LLONG_MAX, "+9223372036854775807", 20, func, 10, NO_ERR));
    C(strtoint_verify(-LLONG_MAX, "-9223372036854775807", 20, func, 10, NO_ERR));

    C(strtoint_verify(        -1, "-18446744073709551616", 21, func, 10, ERANGE));
    C(strtoint_verify(        -1, "18446744073709551616" , 20, func, 10, ERANGE));
    C(strtoint_verify(        -1, "18446744073709551615" , 20, func, 10, NO_ERR));
    C(strtoint_verify(        -1, "+18446744073709551615", 21, func, 10, NO_ERR));
    C(strtoint_verify(         1, "-18446744073709551615", 21, func, 10, NO_ERR));

    C(strtoint_verify( LLONG_MIN, "-1000000000000000000000000000000000000000000000000000000000000000", 65, func, 2, NO_ERR));
    C(strtoint_verify( LLONG_MIN, " 1000000000000000000000000000000000000000000000000000000000000000", 65, func, 2, NO_ERR));
    C(strtoint_verify( LLONG_MAX, "0b111111111111111111111111111111111111111111111111111111111111111", 65, func, 0, NO_ERR));
    C(strtoint_verify(-LLONG_MAX, " -111111111111111111111111111111111111111111111111111111111111111", 65, func, 2, NO_ERR));

    C(strtoint_verify(        -1, "-10000000000000000000000000000000000000000000000000000000000000000", 66, func, 2, ERANGE));
    C(strtoint_verify(        -1, " 10000000000000000000000000000000000000000000000000000000000000000", 66, func, 2, ERANGE));
    C(strtoint_verify(        -1, "0b1111111111111111111111111111111111111111111111111111111111111111", 66, func, 0, NO_ERR));
    C(strtoint_verify(         1, " -1111111111111111111111111111111111111111111111111111111111111111", 66, func, 2, NO_ERR));

    C(strtoint_verify(        -1, "-1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));
    C(strtoint_verify(        -1, "+1qaz2WSX3edc4RFV5tgb", 21, func, 36, ERANGE));

    return 0;
}

//------------------------------------------------------------------------------
// Program
//------------------------------------------------------------------------------

int run_tests(void) {
    int ret = 0;

    /* basic tests of ato* and strto* routines */
    TEST_NAME(atoint_test(atoint_atoi    ), "atoi"    );
    TEST_NAME(atoint_test(atoint_atol    ), "atol"    );
    TEST_NAME(atoint_test(atoint_atoll   ), "atoll"   );
    TEST_NAME(atoint_test(atoint_strtoi  ), "strtoi"  );
    TEST_NAME(atoint_test(atoint_strtoui ), "strtoui" );
    TEST_NAME(atoint_test(atoint_strtol  ), "strtol"  );
    TEST_NAME(atoint_test(atoint_strtoul ), "strtoul" );
    TEST_NAME(atoint_test(atoint_strtoll ), "strtoll" );
    TEST_NAME(atoint_test(atoint_strtoull), "strtoull");

    /* basic tests of strto* routines */
    TEST_NAME(strtoint_test(strtoint_strtol  ), "strtoi"  );
    TEST_NAME(strtoint_test(strtoint_strtoul ), "strtoui" );
    TEST_NAME(strtoint_test(strtoint_strtol  ), "strtol"  );
    TEST_NAME(strtoint_test(strtoint_strtoul ), "strtoul" );
    TEST_NAME(strtoint_test(strtoint_strtoll ), "strtoll" );
    TEST_NAME(strtoint_test(strtoint_strtoull), "strtoull");

    /* specific tests for each routine */
    TEST(test_atoi());
    TEST(test_atol());
    TEST(test_atoll());
    TEST(test_strtol());
    TEST(test_strtoi());
    TEST(test_strtoui());
    TEST(test_strtoul());
    TEST(test_strtoll());
    TEST(test_strtoull());

    /* others */
    TEST(test_char_to_digit());

    return ret;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }

    while (!os_GetCSC());

    return 0;
}
