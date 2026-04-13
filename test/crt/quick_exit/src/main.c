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

void at_quick_exit_func_1(void) {
    printf("first at_quick_exit\n");
    while (!os_GetCSC());
}

void at_quick_exit_func_2(void) {
    puts("most recent at_quick_exit");
    while (!os_GetCSC());
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    errno = 0;
    os_ClrHome();
    if (on_exit(on_exit_func, NULL) != 0) {
        perror("Failed on_exit(on_exit_func, NULL)");
        while (!os_GetCSC());
        return 0;
    }
    if (at_quick_exit(at_quick_exit_func_1) != 0) {
        perror("Failed at_quick_exit(at_quick_exit_func_1)");
        while (!os_GetCSC());
        return 0;
    }
    if (atexit(atexit_func) != 0) {
        perror("Failed on_exit(on_exit_func, NULL)");
        while (!os_GetCSC());
        return 0;
    }
    if (at_quick_exit(at_quick_exit_func_2) != 0) {
        perror("Failed at_quick_exit(at_quick_exit_func_2)");
        while (!os_GetCSC());
        return 0;
    }

    printf("errno: %d\n", errno);

    while (!os_GetCSC());

    quick_exit(EXIT_SUCCESS);
}
