#include <ti/screen.h>
#include <ti/getcsc.h>

__attribute__((constructor(110)))
void ctor_func_110(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

/* the order for destructors and atexit functions is unspecified */

__attribute__((destructor(110)))
void dtor_func_110(void) {
    // have an observable effect
    os_ClrHome();
}

__attribute__((destructor))
void dtor_func_none(void) {
    // have an observable effect
    os_ClrHome();
}
