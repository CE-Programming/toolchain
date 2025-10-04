#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <inttypes.h>
#include <ctype.h>

#define NO_FLOAT    0
#define USE_STRTOD  1
#define USE_STRTOF  2
#define USE_STRTOLD 3

/*============================================================================*/
/* Config                                                                     */
/*============================================================================*/

/**
 * define to 0 or 1. Enables support for `[` set matching (such as "%3[^]^123abc]").
 */
#define ENABLE_SET_MATCHING 1

/**
 * Maximum characters (including null terminator) to scan for set matching.
 * Also determines the highest maximum field width that can be processed.
 * Recommended values:
 * - 128 or 256 if you are not targetting embedded platforms.
 * otherwise, for embedded targets:
 * - 16 allows for digits and a few other symbols to be matched.
 * - 72 allows for lowercase, uppercase, digits, and a few other symbols to be matched.
 */
#define SCAN_LIMIT 40

/**
 * Select the float conversion routine used:
 * NO_FLOAT    : disables float conversion formats.
 * USE_STRTOD  : `strtod`  (default)
 * USE_STRTOF  : `strtof`  (speed)
 * USE_STRTOLD : `strtold` (precision)
 */
#define STRING_TO_FLOAT USE_STRTOD

/**
 * define to 0 or 1. Adds support for C23 `%b` format specifiers.
 */
#define ENABLE_BINARY_CONVERSION_FORMAT 1

/**
 * define to `restrict`, `__restrict`, `__restrict__`, or leave blank.
 */
#define NANO_SCANF_restrict __restrict

/*============================================================================*/
/* Validate macros                                                            */
/*============================================================================*/

/* minimum size to read "-32768" */
#if SCAN_LIMIT < 7
# error "SCAN_LIMIT is too small"
#endif

#ifndef STRING_TO_FLOAT
# error "STRING_TO_FLOAT must be defined to a value"
#endif

#if STRING_TO_FLOAT == USE_STRTOD
# define STRING_TO_FLOAT_TYPE double
# define STRING_TO_FLOAT_FUNC strtod
#elif STRING_TO_FLOAT == USE_STRTOF
# define STRING_TO_FLOAT_TYPE float
# define STRING_TO_FLOAT_FUNC strtof
#elif STRING_TO_FLOAT == USE_STRTOLD
# define STRING_TO_FLOAT_TYPE long double
# define STRING_TO_FLOAT_FUNC strtold
#elif STRING_TO_FLOAT != NO_FLOAT
# error "invalid STRING_TO_FLOAT value"
#endif

#ifndef ENABLE_SET_MATCHING
# error "ENABLE_SET_MATCHING must be defined to 0 or 1"
#endif

#ifndef ENABLE_BINARY_CONVERSION_FORMAT
# error "ENABLE_BINARY_CONVERSION_FORMAT must be defined to 0 or 1"
#endif

#if UINTMAX_MAX < ULLONG_MAX
#error "UINTMAX_MAX needs to be greater than or equal ULLONG_MAX"
#endif

/*============================================================================*/
/* Code                                                                       */
/*============================================================================*/

#define TEST_LENGTH_MODIFIER() do { \
    if (ptr_size == 0) { \
        /* invalid length modifier */ \
        return assignment_count; \
    } \
} while (0)

#define CONSUME_WHITESPACE() while (isspace(*buf)) { buf++; }

#define RETURN_IF_NULL(ptr) if ((ptr) == NULL) { return assignment_count; }

static intmax_t limit_strtoimax(
    char const * NANO_SCANF_restrict str,
    char * * NANO_SCANF_restrict endptr,
    int base,
    size_t max_len,
    char * NANO_SCANF_restrict scan_buf
) {
    if (max_len == 0) {
        return strtoimax(str, (char**)endptr, base);
    }
    size_t copy_size = ((max_len + 1) > SCAN_LIMIT) ? SCAN_LIMIT : (max_len + 1);
    strncpy(scan_buf, str, copy_size);
    /* null terminate */
    scan_buf[copy_size - 1] = '\0';
    char* scan_endptr;
    intmax_t value = strtoimax(scan_buf, &scan_endptr, base);
    *endptr = (char*)(str + (scan_endptr - scan_buf));
    return value;
}

static uintmax_t limit_strtoumax(
    char const * NANO_SCANF_restrict str,
    char * * NANO_SCANF_restrict endptr,
    int base,
    size_t max_len,
    char * NANO_SCANF_restrict scan_buf
) {
    if (max_len == 0) {
        return strtoumax(str, (char**)endptr, base);
    }
    size_t copy_size = ((max_len + 1) > SCAN_LIMIT) ? SCAN_LIMIT : (max_len + 1);
    strncpy(scan_buf, str, copy_size);
    /* null terminate */
    scan_buf[copy_size - 1] = '\0';
    char* scan_endptr;
    uintmax_t value = strtoumax(scan_buf, &scan_endptr, base);
    *endptr = (char*)(str + (scan_endptr - scan_buf));
    return value;
}

#if STRING_TO_FLOAT
static STRING_TO_FLOAT_TYPE limit_strtofloat(
    char const * NANO_SCANF_restrict str,
    char * * NANO_SCANF_restrict endptr,
    size_t max_len,
    char * NANO_SCANF_restrict scan_buf
) {
    if (max_len == 0) {
        return STRING_TO_FLOAT_FUNC(str, (char**)endptr);
    }
    size_t copy_size = ((max_len + 1) > SCAN_LIMIT) ? SCAN_LIMIT : (max_len + 1);
    strncpy(scan_buf, str, copy_size);
    /* null terminate */
    scan_buf[copy_size - 1] = '\0';
    char* scan_endptr;
    STRING_TO_FLOAT_TYPE value = STRING_TO_FLOAT_FUNC(scan_buf, &scan_endptr);
    *endptr = (char*)(str + (scan_endptr - scan_buf));
    return value;
}
#endif /* STRING_TO_FLOAT */

/**
 * @author zerico2005 (Originally based off of https://github.com/tusharjois/bscanf)
 * @note All non-suppressed character sequence types must have a maximum field width:
 *  - Valid   : "%*3c %*8s %*12[^abc]"
 *  - Valid   : "%3c  %8s  %12[^abc]"
 *  - Valid   : "%*c  %*s  %*[^abc]"
 *  - Invalid : "%c   %s   %[^abc]"
 * @note ranges such as "%5[0-9]" or "%5[^a-z]" are not supported
 * @note Assumes little endian
 * @note `wchar_t` is not supported
 */
int vsscanf(
    char const * const NANO_SCANF_restrict Buffer,
    char const * const NANO_SCANF_restrict Format,
    va_list args
) {
    char scan_buf[SCAN_LIMIT];
    int assignment_count = 0;
    char const * NANO_SCANF_restrict buf = Buffer;
    char const * NANO_SCANF_restrict fmt = Format;
    if (buf == NULL || fmt == NULL) {
        return EOF;
    }
    while (*fmt != '\0') {
        if (isspace(*fmt)) {
            CONSUME_WHITESPACE();
            fmt++;
            continue;
        }
        if (*fmt != '%') {
            if (*fmt != *buf) {
                /* end of format */
                return assignment_count;
            }
            fmt++;
            buf++;
            continue;
        }
        /* conversion specifier */
        fmt++;
        bool is_suppressed = false;
        bool is_double_or_wide_char = false;
    #if STRING_TO_FLOAT
        bool is_long_double = false;
    #endif /* STRING_TO_FLOAT */
        size_t max_width = 0;
        size_t ptr_size = sizeof(int);
        if (*fmt == '*') {
            is_suppressed = true;
            fmt++;
        }
        /* test for digits */
        if (isdigit(*fmt)) {
            char *endptr;
            /**
             * @remarks Either strtoumax or strtoul can be used here.
             * strtoul might be faster, however it also means that we link
             * another routine increasing size. So strtoumax is used instead so
             * use can reduce the amount of routines we need to link to.
             */
            max_width = (size_t)strtoumax(fmt, &endptr, 10);
            if (fmt == endptr || max_width == 0) {
                /* failed */
                return assignment_count;
            }
            fmt = endptr;
        }
        /* test for length modifiers */
        switch (*fmt) {
            case 'h':
            {
                ptr_size = sizeof(short);
                fmt++;
                if (*fmt == 'h') {
                    ptr_size = sizeof(char);
                    fmt++;
                }
            } break;
            case 'z':
            {
                ptr_size = sizeof(size_t);
                fmt++;
            } break;
            case 'l':
            {
                is_double_or_wide_char = true;
                ptr_size = sizeof(long);
                fmt++;
                if (*fmt == 'l') {
                    ptr_size = sizeof(long long);
                    fmt++;
                }
            } break;
            case 't':
            {
                ptr_size = sizeof(ptrdiff_t);
                fmt++;
            } break;
        #if STRING_TO_FLOAT
            case 'L':
            {
                is_long_double = true;
                ptr_size = 0;
                fmt++;
            } break;
        #endif /* STRING_TO_FLOAT */
            case 'j':
            {
                ptr_size = sizeof(intmax_t);
                fmt++;
            } break;
            default: break;
        }
        /**
         * @remarks All conversion specifiers other than 'n' 'c' '[' consume
         * and discard all leading whitespace characters.
         */
        if (*fmt != 'n' && *fmt != 'c' && *fmt != '[') {
            CONSUME_WHITESPACE();
        }
        /* test for format type */
        switch (*fmt) {
            case '%':
            /* handle "%%" */ {
                if (*fmt != *buf) {
                    return assignment_count;
                }
                buf++;
                fmt++;
                continue;
            }
            case 'n':
            /* number of characters read so far */ {
                if (is_suppressed) {
                    /* "%*n" is undefined behaviour */
                    return assignment_count;
                }
                TEST_LENGTH_MODIFIER();
                void* ptr = va_arg(args, void*);
                RETURN_IF_NULL(ptr);
                unsigned long long diff = buf - Buffer;
                memcpy(ptr, &diff, ptr_size);
                fmt++;
                /* assignment_count is not incremented for %n */
                continue;
            } break;
            case 'c':
            case 's':
            /* string */ {
                const bool string_format = (*fmt == 's');
                if (!is_suppressed && max_width == 0) {
                    /* enforce bounds checking */
                    return assignment_count;
                }
                if (is_double_or_wide_char) {
                    /* unimplemented */
                    return assignment_count;
                }
                char const * NANO_SCANF_restrict const begin = buf;
                for (; max_width --> 0;) {
                    if (*buf == '\0') {
                        break;
                    }
                    if (string_format && isspace(*buf)) {
                        break;
                    }
                    buf++;
                }
                size_t copy_size = buf - begin;
                if (!is_suppressed) {
                    char* ptr = va_arg(args, char*);
                    RETURN_IF_NULL(ptr);
                    memcpy(ptr, begin, copy_size);
                    if (string_format) {
                        /* null terminate */
                        *(ptr + copy_size) = '\0';
                    }
                    assignment_count++;
                }
                fmt++;
                continue;
            } break;
        #if ENABLE_SET_MATCHING
            case '[':
            /* match range */ {
                fmt++;
                if (!is_suppressed && max_width == 0) {
                    /* enforce bounds checking */
                    return assignment_count;
                }
                if (is_double_or_wide_char) {
                    /* unimplemented */
                    return assignment_count;
                }
                bool invert_match = false;
                bool starts_with_bracket = false;
                if (*fmt == '^') {
                    invert_match = true;
                    fmt++;
                }
                if (*fmt == ']') {
                    starts_with_bracket = true;
                    fmt++;
                }
                char const * NANO_SCANF_restrict last_bracket = strchr(fmt, ']');
                if (last_bracket == NULL) {
                    /* "%[^]" is still considered to be an empty sequence */
                    return assignment_count;
                }
                if (starts_with_bracket) {
                    fmt--;
                }
                size_t scan_length = (last_bracket - fmt);

                if (scan_length >= SCAN_LIMIT) {
                    /* too many characters */
                    return assignment_count;
                }
                memcpy(scan_buf, fmt, scan_length);
                /* null terminate */
                *(scan_buf + scan_length) = '\0';
                /* move format to the character after the ending ']' */
                fmt = last_bracket + 1;

                size_t match_length;
                if (invert_match) {
                    match_length = strcspn(buf, scan_buf);
                } else {
                    match_length = strspn(buf, scan_buf);
                }
                if (max_width != 0 && match_length > max_width) {
                    match_length = max_width;
                }

                if (!is_suppressed) {
                    char* ptr = va_arg(args, char*);
                    RETURN_IF_NULL(ptr);
                    memcpy(ptr, buf, match_length);
                    /* null terminate */
                    *(ptr + match_length) = '\0';
                    assignment_count++;
                }
                /* move buf to the character after the last matched character */
                buf += match_length;
                continue;
            } break;
        #endif /* ENABLE_SET_MATCHING */
            case 'i':
            case 'd':
            /* signed integer */ {
                TEST_LENGTH_MODIFIER();
                char *endptr;
                int base = ((*fmt == 'd') ? 10 : 0);
                intmax_t value = limit_strtoimax(buf, &endptr, base, max_width, scan_buf);
                if (buf == endptr) {
                    /* failed */
                    return assignment_count;
                }
                if (!is_suppressed) {
                    void* ptr = va_arg(args, void*);
                    RETURN_IF_NULL(ptr);
                    memcpy(ptr, &value, ptr_size);
                    assignment_count++;
                }
                buf = endptr;
                fmt++;
            } break;
        #if ENABLE_BINARY_CONVERSION_FORMAT
            case 'b':
        #endif /* ENABLE_BINARY_CONVERSION_FORMAT */
            case 'u':
            case 'o':
            case 'x':
            case 'X':
            case 'p':
            /* unsigned integer or pointer */ {
                TEST_LENGTH_MODIFIER();
                char *endptr;
                int base = 10;
                if (*fmt == 'X' || *fmt == 'x' || *fmt == 'p') {
                    base = 16;
                    if (*fmt == 'p') {
                        ptr_size = sizeof(void*);
                    }
            #if ENABLE_BINARY_CONVERSION_FORMAT
                } else if (*fmt == 'b') {
                    base = 2;
            #endif /* ENABLE_BINARY_CONVERSION_FORMAT*/
                } else if (*fmt == 'o') {
                    base = 8;
                }
                uintmax_t value = limit_strtoumax(buf, &endptr, base, max_width, scan_buf);
                if (buf == endptr) {
                    /* failed */
                    return assignment_count;
                }
                if (!is_suppressed) {
                    void* ptr = va_arg(args, void*);
                    RETURN_IF_NULL(ptr);
                    memcpy(ptr, &value, ptr_size);
                    assignment_count++;
                }
                buf = endptr;
                fmt++;
            } break;
        #if STRING_TO_FLOAT
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'f':
            case 'F':
            case 'g':
            case 'G':
            /* float */ {
                char *endptr;
                STRING_TO_FLOAT_TYPE value = limit_strtofloat(buf, &endptr, max_width, scan_buf);
                if (buf == endptr) {
                    /* failed */
                    return assignment_count;
                }
                if (!is_suppressed) {
                    void* ptr = va_arg(args, void*);
                    RETURN_IF_NULL(ptr);
                    if (is_long_double) {
                        *(long double*)ptr = (long double)value;
                    } else if (is_double_or_wide_char) {
                        *(double*)ptr = (double)value;
                    } else {
                        *(float*)ptr = (float)value;
                    }
                    assignment_count++;
                }
                buf = endptr;
                fmt++;
            } break;
        #endif /* STRING_TO_FLOAT */
            default:
            /* unknown format */ {
                return assignment_count;
            } break;
        }
    }
    return assignment_count;
}

int sscanf(const char * NANO_SCANF_restrict buffer, const char * NANO_SCANF_restrict format, ...)
{
    va_list vlist;
    va_start(vlist, format);
    int ret = vsscanf(buffer, format, vlist);
    va_end(vlist);
    return ret;
}
