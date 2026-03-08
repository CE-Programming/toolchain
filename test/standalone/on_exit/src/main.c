#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

void cleanup(int status, void *arg) {
    const char *message = (char*)arg;

    gfx_PrintStringXY(message, 10, 30);

    gfx_PrintStringXY("Exit status: ", 10, 50);
    gfx_PrintInt(status, 1);

    while (!os_GetCSC());
}

void final_func(void) {
    os_ClrHome();
    puts("Finished tests");
    while (!os_GetCSC());
}

int main(void) {
    errno = 0;
    os_ClrHome();
    const char *msg = "cleanup func";
    if (atexit(final_func) != 0) {
        perror("Failed atexit(final_func)");
        while (!os_GetCSC());
        return 0;
    }
    if (atexit(gfx_End) != 0) {
        perror("Failed atexit(gfx_End)");
        while (!os_GetCSC());
        return 0;
    }
    if (on_exit(cleanup, (void*)msg) != 0) {
        perror("Failed on_exit(cleanup, msg)");
        while (!os_GetCSC());
        return 0;
    }

    gfx_Begin();

    gfx_PrintStringXY("errno: ", 10, 10);
    gfx_PrintInt(errno, 1);

    while (!os_GetCSC());

    return 7184;
}
