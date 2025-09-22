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
#include <limits.h>
#include <ti/sprintf.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

#define C(expr) if (!(expr)) { return __LINE__; }

#define T(val, expr) do { \
    long long temp = (long long)(expr); \
    if ((long long)(val) != temp) { \
        test_printf("E: %lld\n", temp); \
        return __LINE__; \
    } \
} while (0);

#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

int test_atoi(void) {
    T(   0, atoi(""             ));
    T(   0, atoi("+"            ));
    T(   0, atoi("-"            ));
    T(   0, atoi("0"            ));
    T(   0, atoi("+0"           ));
    T(   0, atoi("-0"           ));
    T(   1, atoi("1"            ));
    T(   1, atoi("+1"           ));
    T(  -1, atoi("-1"           ));
    T(   0, atoi("+-84"         ));
    T(   0, atoi("--84"         ));
    T(   0, atoi("-+84"         ));
    T(   0, atoi("++84"         ));
    T(   0, atoi("+ 84"         ));
    T(   0, atoi("- 84"         ));
    T( 100, atoi("100"          ));
    T( 100, atoi("+100"         ));
    T(-100, atoi("-100"         ));
    T(-123, atoi(" -123junk"    ));
    T( 321, atoi(" +321dust"    ));
    T(  99, atoi(" \f\n\r\t\v99"));
    T(  42, atoi("0042"         ));
    T(   0, atoi("0x2A"         ));
    T(   0, atoi("junk"         ));
    T(   0, atoi("a701"         ));

    T( INT_MIN, atoi("-8388608" ));
    T( INT_MAX, atoi("8388607"  ));
    T( INT_MAX, atoi("+8388607" ));
    T(-INT_MAX, atoi("-8388607" ));
    return 0;
}

int test_atol(void) {
    T(   0, atol(""             ));
    T(   0, atol("+"            ));
    T(   0, atol("-"            ));
    T(   0, atol("0"            ));
    T(   0, atol("+0"           ));
    T(   0, atol("-0"           ));
    T(   1, atol("1"            ));
    T(   1, atol("+1"           ));
    T(  -1, atol("-1"           ));
    T(   0, atol("+-84"         ));
    T(   0, atol("--84"         ));
    T(   0, atol("-+84"         ));
    T(   0, atol("++84"         ));
    T(   0, atol("+ 84"         ));
    T(   0, atol("- 84"         ));
    T( 100, atol("100"          ));
    T( 100, atol("+100"         ));
    T(-100, atol("-100"         ));
    T(-123, atol(" -123junk"    ));
    T( 321, atol(" +321dust"    ));
    T(  99, atol(" \f\n\r\t\v99"));
    T(  42, atol("0042"         ));
    T(   0, atol("0x2A"         ));
    T(   0, atol("junk"         ));
    T(   0, atol("a701"         ));

    T( LONG_MIN, atol("-2147483648"));
    T( LONG_MAX, atol("2147483647"));
    T( LONG_MAX, atol("+2147483647"));
    T(-LONG_MAX, atol("-2147483647"));
    return 0;
}

int test_atoll(void) {
    T(   0, atoll(""             ));
    T(   0, atoll("+"            ));
    T(   0, atoll("-"            ));
    T(   0, atoll("0"            ));
    T(   0, atoll("+0"           ));
    T(   0, atoll("-0"           ));
    T(   1, atoll("1"            ));
    T(   1, atoll("+1"           ));
    T(  -1, atoll("-1"           ));
    T(   0, atoll("+-84"         ));
    T(   0, atoll("--84"         ));
    T(   0, atoll("-+84"         ));
    T(   0, atoll("++84"         ));
    T(   0, atoll("+ 84"         ));
    T(   0, atoll("- 84"         ));
    T( 100, atoll("100"          ));
    T( 100, atoll("+100"         ));
    T(-100, atoll("-100"         ));
    T(-123, atoll(" -123junk"    ));
    T( 321, atoll(" +321dust"    ));
    T(  99, atoll(" \f\n\r\t\v99"));
    T(  42, atoll("0042"         ));
    T(   0, atoll("0x2A"         ));
    T(   0, atoll("junk"         ));
    T(   0, atoll("a701"         ));

    T( LLONG_MIN, atoll("-9223372036854775808"));
    T( LLONG_MAX, atoll("9223372036854775807"));
    T( LLONG_MAX, atoll("+9223372036854775807"));
    T(-LLONG_MAX, atoll("-9223372036854775807"));
    return 0;
}

int run_tests(void) {
    int ret = 0;

    TEST(test_atoi());
    TEST(test_atol());
    TEST(test_atoll());

    return ret;
}

int main(void) {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608\n")];
        boot_sprintf(buf, "Failed test L%d\n", failed_test);
        fputs(buf, stdout);
    } else {
        fputs("All tests passed", stdout);
    }

    while (!os_GetCSC());

    return 0;
}
