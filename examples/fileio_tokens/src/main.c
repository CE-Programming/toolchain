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
    uint8_t *data_ptr;
    
    /* Close any files that may be open already */
    ti_CloseAll();
    
    /* Open the program for reading */
    prgm = ti_OpenVar(prgmName, "r", TI_PRGM_TYPE);
    
    /* Make sure we opened okay */
    if (!prgm) goto err;

    data_ptr = ti_GetDataPtr(prgm);
    printText(0, 0, ti_GetTokenString(&data_ptr, NULL, NULL));
    printText(0, 1, ti_GetTokenString(&data_ptr, NULL, NULL));
    
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
