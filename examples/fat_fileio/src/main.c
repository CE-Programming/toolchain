#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <usbfatce.h>

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);
void init_msd(void);

/* Main Function */
void main(void) {
    os_ClrHome();

    init_msd();

    while (!os_GetCSC());
}

void init_msd(void) {

    printText(0, 0, "insert msd...");

    /* initialize mass storage device */
    if (!msd_Init()) {
        printText(0, 1, "msd init failed.");
        return;
    }

    printText(0, 1, "locating filesystem");
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
