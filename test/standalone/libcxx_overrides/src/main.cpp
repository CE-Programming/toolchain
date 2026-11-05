#include <cstdio>
#include <ti/getcsc.h>
#include <ti/screen.h>

bool test_function_overrides();
int replaced_hook() { return 33; }

int main(void) {
    os_ClrHome();

    int failed_test = test_function_overrides() ? 0 : __LINE__;
    if (failed_test != 0) {
        std::printf("Failed test L%d\n", failed_test);
    } else {
        std::printf("All tests passed");
    }

    while (!os_GetCSC())
        ;

    return 0;
}
