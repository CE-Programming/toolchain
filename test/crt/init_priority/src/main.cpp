#include <ti/screen.h>
#include <ti/getcsc.h>

#include <stdio.h>
#include <string.h>

#include "ordered_event.h"

/* the following functions are intentionally defined in a random order */

OrderedEvent init_101 __attribute__((init_priority(101)))("init_ctor_101", "init_dtor_101");
OrderedEvent init_none("init_ctor_none", "init_dtor_none");
OrderedEvent init_121 __attribute__((init_priority(121)))("init_ctor_121", "init_dtor_121");

int main(int argc, char * argv[]) {
    os_ClrHome();

    if (argc != 1) {
        os_PutStrFull("unexpected argc");
        while (!os_GetCSC());
        return 0;
    }
    if (strcmp(argv[0], "DEMO") != 0) {
        os_PutStrFull("unexpected argv[0]");
        while (!os_GetCSC());
        return 0;
    }
    if (argv[1] != nullptr) {
        os_PutStrFull("unexpected argv[1]");
        while (!os_GetCSC());
        return 0;
    }

    os_PutStrFull("main_func");
    while (!os_GetCSC());

    return 0;
}
