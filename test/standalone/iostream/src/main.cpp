#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>
#include <cstdio>
#include <iostream>

int main(void) {
    os_ClrHome();

    int value = 123;
    volatile bool* test = (volatile bool*)0xE40000;
    if (*test) {
        std::cout << value;
    }

    while (!os_GetCSC());

    return 0;
}
