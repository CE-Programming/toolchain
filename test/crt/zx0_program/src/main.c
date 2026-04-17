#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <sys/util.h>

#include <stddef.h>
#include <stdio.h>

int arr[] = {
    0, 1,
    0, 0, 1, 1,
    0, 0, 0, 1, 1, 1,
    0, 0, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    0, -1,
    0, 0, -1, -1,
    0, 0, 0, -1, -1, -1,
    0, 0, 0, 0, -1, -1, -1, -1,
    0, 0, 0, 0, 0, -1, -1, -1, -1, -1,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1,
    0, 0, 1, 1,
    0, 1,
};

// does nothing with the array
int disable_compile_time_evaluation(int *);

int main(void) {
    os_ClrHome();

    if (disable_compile_time_evaluation(arr) != 42) {
        puts("unexpected value");
        while (!os_GetCSC());
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        sum += arr[i];
    }
    char buf[sizeof("sum = -8388608")];
    boot_sprintf(buf, "sum = %d", sum);
    puts(buf);

    while (!os_GetCSC());

    return 0;
}
