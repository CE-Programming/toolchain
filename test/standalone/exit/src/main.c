#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanup(int status, void *arg) {
    if (arg != NULL) {
        printf("expected NULL: %p\n", arg);
    }
    printf("Exit status: %d\n", status);

    while (!os_GetCSC());
}

int main(void) {
    errno = 0;
    os_ClrHome();
    if (on_exit(cleanup, NULL) != 0) {
        perror("Failed on_exit(cleanup, NULL)");
        while (!os_GetCSC());
        return 0;
    }

    printf("errno: %d\n", errno);

    while (!os_GetCSC());

    exit(42);
}
