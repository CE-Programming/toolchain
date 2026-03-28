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

#define C(expr) if (!(expr)) { return __LINE__; }

int run_tests(void) {
    char buf[40];
    memset(buf, '\0', sizeof(buf));
    {
        // do a very simple test to see if nanoprintf_nofloat is working
        int value = 123;
        const char * truth = "123";
        C(snprintf(buf, sizeof(buf), "%d", value) == 3);
        C(strcmp(buf, truth) == 0);
    }
    {
        // make sure we are not using boot_sprintf
        intmax_t value = 0x123456789ABCDEF;
        const char * truth = "0X123456789ABCDEF";
        C(sprintf(buf, "%#jX", value) == 17);
        C(strcmp(buf, truth) == 0);
    }
    {
        // test writeback formatting
        int offset_1 = 0x555555;
        char offset_2 = 0xAA;
        int value_1 = 456;
        unsigned value_2 = 77;
        const char * truth = "+456%77";
        C(snprintf(buf, sizeof(buf), "%+i%n%%%u%hhn", value_1, &offset_1, value_2, &offset_2) == 7);
        C(offset_1 == 4);
        C(offset_2 == 7);
        C(strcmp(buf, truth) == 0);
    }
    // we have now proven that nanoprintf_nofloat works with integers
    {
        /**
         * Since we are linking nanoprintf_nofloat, we should test that floats
         * do not work. This means that it shouldn't print 1.000000 or
         * something else like that. Otherwise main thing we are testing for
         * is that no crashes occur.
         */
        double value_1 = 1.0;
        long double value_2 = 1.0L;

        snprintf(buf, sizeof(buf) - 1, "%f", value_1);
        // make sure we did not just print garbage
        C(strnlen(buf, sizeof(buf)) < sizeof(buf));
        // test that we did not print a number
        C(strchr(buf, '1') == NULL);
        C(strchr(buf, '0') == NULL);
        C(strchr(buf, '.') == NULL);

        sprintf(buf, "%lf", value_1);
        // make sure we did not just print garbage
        C(strnlen(buf, sizeof(buf)) < sizeof(buf));
        // test that we did not print a number
        C(strchr(buf, '1') == NULL);
        C(strchr(buf, '0') == NULL);
        C(strchr(buf, '.') == NULL);

        snprintf(buf, sizeof(buf) - 1, "%Lf", value_2);
        // make sure we did not just print garbage
        C(strnlen(buf, sizeof(buf)) < sizeof(buf));
        // test that we did not print a number
        C(strchr(buf, '1') == NULL);
        C(strchr(buf, '0') == NULL);
        C(strchr(buf, '.') == NULL);
    }

    return 0;
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
