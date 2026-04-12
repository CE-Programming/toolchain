#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>
#include <stdio.h>
#include <fenv.h>

#include "func.h"

#define TEST(test) do { \
    ret = test; \
    if (ret != 0) { \
        puts("failed " #test); \
        return ret; \
    } \
} while(0)

int run_tests(void) {
    int ret = 0;

    TEST(test_1_c());
    TEST(test_2_cpp());
    TEST(test_3_asm());
    TEST(test_4_c());
    TEST(test_5_cpp());

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
