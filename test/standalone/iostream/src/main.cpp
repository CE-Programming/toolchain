#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>
#include <ti/sprintf.h>
#include <cstdio>
#include <iostream>

extern "C" void init_iostream(void);

int main(void) {
    init_iostream();

    os_ClrHome();

    int value = 123;
    printf("start: %d\n", value);

    volatile bool* test = (volatile bool*)0xE40000;
    if (true || *test) {
        std::cout << value;
    }

    while (!os_GetCSC());

    return 0;
}
