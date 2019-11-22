#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fileioc.h>

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

/* Main Function */
void main(void) {
    /* Declare some variables -- search_pos must be NULL to begin with */
    void *search_pos = NULL;
    uint8_t type;
    char *var_name;
    int8_t y = 0;

    /* First couple bytes of the LibLoad AppVar, which is known to exist */
    /* Technically is a null-terminated string, if an odd looking one */
    const char search_string[] = { 0xBF, 0xFE, 0x00 };

    /* Clear the homescreen */
    os_ClrHome();

    /* Find all of the variables that start with this string */
    while ((var_name = ti_DetectAny(&search_pos, search_string, &type)) != NULL) {
        if (type == TI_APPVAR_TYPE) {
            /* Print the name of the variable (Should be LibLoad) */
            printText(0, y++, var_name);
        }
    }

    /* Wait for a key */
    while (!os_GetCSC());

    /* Close all open files */
    ti_CloseAll();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
