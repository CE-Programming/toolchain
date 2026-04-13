#include <ti/screen.h>
#include <ti/getcsc.h>

/* the following functions are intentionally defined in a random order */

__attribute__((destructor(0)))
void dtor_func_0(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((constructor(50)))
void ctor_func_50(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((constructor(0)))
void ctor_func_0(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((constructor(100))) __attribute__((destructor(100)))
void both_ctor_dtor_100(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((destructor))
void dtor_func_none(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((destructor(120)))
void dtor_func_120(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

__attribute__((constructor))
void ctor_func_none(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

void random_func(void) {
    os_ClrHome();
    os_PutStrFull(__FUNCTION__);
    while (!os_GetCSC());
}

int main(void) {
    os_ClrHome();
    os_PutStrFull("main_func");
    while (!os_GetCSC());

    return 0;
}
