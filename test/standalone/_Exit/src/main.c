#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void atexit_func(void) {
    printf("atexit_func called\n");
    while (!os_GetCSC());
}

void on_exit_func(int status, void *arg) {
    printf("on_exit_func called\n");
    printf("status: %d\narg: %p\n", status, arg);
    while (!os_GetCSC());
}

int main(void) {
    errno = 0;
    os_ClrHome();
    if (on_exit(on_exit_func, NULL) != 0) {
        perror("Failed on_exit(on_exit_func, NULL)");
        while (!os_GetCSC());
        return 0;
    }
    if (atexit(atexit_func) != 0) {
        perror("Failed on_exit(on_exit_func, NULL)");
        while (!os_GetCSC());
        return 0;
    }

    printf("errno: %d\n", errno);

    while (!os_GetCSC());

    _Exit(EXIT_SUCCESS);
}
