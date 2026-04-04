#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <stdio.h>
#include <stdlib.h>

extern int malloc_calls;

void atexit_func(void) {
    /*
     * The custom free function is supposed to print a string if it is called,
     * however, it is unspecified if atexit_func or free will be called first.
     * This means that we cannot print anything in this function since we
     * cannot guarantee the order. However, this function must be non-empty so
     * Clang does not optimize away the call to atexit. Now some of this could
     * be fixed with -ffreestanding, but that may also hide the assumptions
     * that Clang makes.
     */
    if (*(const char*)-1 != 0) {
        puts("0xFFFFFF should be zero");
        while (!os_GetCSC());
    }
}

int main(void) {
    char buf[50];
    os_ClrHome();

    // CRT0 may use malloc/free so we cannot assume this is zero
    int malloc_calls_before = malloc_calls;

    // calloc should call the custom malloc
    int *ptr = calloc(1, sizeof(int[3]));

    if (ptr == NULL) {
        puts("calloc failed");
        while (!os_GetCSC());
        return 0;
    }

    for (int n = 0; n < 3; ++n) {
        boot_sprintf(buf, "ptr(%d) == %d", n, ptr[n]);
        puts(buf);
    }

    while (!os_GetCSC());

    if (atexit(atexit_func) != 0) {
        puts("atexit(atexit_func) failed");
        while (!os_GetCSC());
        return 0;
    }

    // we expect malloc to be called twice (for calloc and atexit)
    int malloc_call_count = malloc_calls - malloc_calls_before;
    boot_sprintf(buf, "malloc calls: %d", malloc_call_count);
    puts(buf);

    while (!os_GetCSC());

    exit(EXIT_SUCCESS);
}
