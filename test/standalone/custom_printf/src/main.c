#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <stdio.h>

int main(void) {
    char buf[50];
    os_ClrHome();

    // test that we are using a custom printf and not the real one
    const char *str = "printf";
    int result = sprintf(buf, "custom %s!", str);
    puts(buf);
    boot_sprintf(buf, "returned %d", result);
    puts(buf);

    while (!os_GetCSC());

    return 0;
}
