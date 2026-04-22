#include <stdio.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <sys/util.h>

int run_tests(void);

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
