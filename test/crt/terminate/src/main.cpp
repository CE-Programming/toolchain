#include <ti/screen.h>
#include <ti/getcsc.h>
#include <exception>

int main(void) {
    os_ClrHome();
    os_PutStrFull("before std::terminate");
    while (!os_GetCSC());

    std::terminate();
}
