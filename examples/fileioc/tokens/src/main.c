#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fileioc.h>

/* Declare the program name */
const char *prgmName = "ABC";

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

/* Main Function */
void main(void) {
    ti_var_t prgm;
    void *data_ptr;
    uint8_t token_length;
    uint16_t size;
    int8_t y = 0;

    /* Clear the homescreen */
    os_ClrHome();

    /* Close any files that may be open already */
    ti_CloseAll();

    /* Open the program for reading */
    prgm = ti_OpenVar(prgmName, "r", TI_PRGM_TYPE);

    /* Make sure we opened okay */
    if (!prgm) goto err;

    data_ptr = ti_GetDataPtr(prgm);
    size = ti_GetSize(prgm);

    while (size && y < 8) {
        printText(0, y++, ti_GetTokenString(&data_ptr, &token_length, NULL));
        size -= token_length;
    }

err:
    /* Pause */
    while (!os_GetCSC());

    /* Close files */
    ti_CloseAll();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
