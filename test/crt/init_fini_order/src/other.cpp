#include <ti/screen.h>
#include <ti/getcsc.h>

/* test that the ctor/dtor order works with multiple translation units */

__attribute__((constructor(120)))
void ctor_func_120(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((destructor(50)))
void dtor_func_50(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

void other_func(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}
