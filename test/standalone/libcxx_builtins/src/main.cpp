#include <cstdio>
#include <ti/getcsc.h>
#include <ti/screen.h>

int test_compiler_builtins();

int main(void) {
    os_ClrHome();

    int failed_test = test_compiler_builtins();
    if (failed_test != 0) {
        std::printf("Failed test L%d\n", failed_test);
    } else {
        std::printf("All tests passed");
    }

    while (!os_GetCSC())
        ;

    return 0;
}
