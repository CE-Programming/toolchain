#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

void main(void) {
    /* Clear the homescreen */
    os_ClrHome();

    os_PutStrFull("Waiting for 5000 ms...");
    delay(5000);
    os_SetCursorPos(1, 22);
    os_PutStrFull("Done");
    delay(100);
}
