#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

// define to 0 or 1
#define DEBUG_DIAGNOSTICS 0

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------

#define C(expr) if (!(expr)) { return __LINE__; }

#define TEST(test) { ret = test; if (ret != 0) { return ret; }}

#ifndef DEBUG_DIAGNOSTICS
#error "DEBUG_DIAGNOSTICS needs to be defined to 0 or 1"
#endif

#if DEBUG_DIAGNOSTICS
#define test_printf printf
#else
#define test_printf(...)
#endif

//------------------------------------------------------------------------------
// Tests
//------------------------------------------------------------------------------

int link_test(void);

int run_tests(void) {
    int ret = 0;

    TEST(link_test());

    /* passed all */
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
