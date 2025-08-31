#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>
#include <cstdio>

int test();

int main(void) {
    os_ClrHome();
    int failed_test = test();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608\n")];
        boot_sprintf(buf, "Failed test L%d\n", failed_test);
        std::fputs(buf, stdout);
    } else {
        std::fputs("All tests passed", stdout);
    }

    while (!os_GetCSC());

    return 0;
}
