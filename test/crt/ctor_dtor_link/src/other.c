#include <ti/screen.h>
#include <ti/getcsc.h>

/* test that constructors/destructors are linked from other translation units */

/* test constructor with a priority */
__attribute__((constructor(123)))
void ctor_func(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

/* test destructor without a priority */
__attribute__((destructor))
void dtor_func(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}
