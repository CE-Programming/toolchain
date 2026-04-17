#include <ti/screen.h>
#include <ti/getcsc.h>

int main(void) {
    os_ClrHome();
    os_PutStrFull("main_func");
    while (!os_GetCSC());

    return 0;
}
