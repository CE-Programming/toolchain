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
    /* Declare some variables */
    const char *oldName = "OldFile";
    const char *newName = "NewFile";
    char nameBuffer[10];
    ti_var_t file;
    bool err = true;

    /* Clear the homescreen */
    os_ClrHome();

    /* Close any previously open files */
    ti_CloseAll();

    /* Delete both the new and old files if they already exist */
    ti_Delete(oldName);
    ti_Delete(newName);

    do {
        /* Create a file with the old name */
        file = ti_Open(oldName, "w");
        if (!file) break;

        ti_GetName(nameBuffer, file);
        printText(0, 0, "Old Name: ");
        printText(10, 0, nameBuffer);

        /* Rename the old file to the new file name */
        /* Note: This function closes all open files! */
        ti_Rename(oldName, newName);

        /* Ensure the new name of the file is correct */
        file = ti_Open(newName, "r");
        if (!file) break;

        ti_GetName(nameBuffer, file);
        printText(0, 1, "New Name: ");
        printText(10, 1, nameBuffer);

        err = false;
    } while (0);

    /* Close all open files */
    ti_CloseAll();

    /* If an error occured, inform the user */
    if (err == true) {
        printText(0, 2, "An error occured");
    }

    /* Wait for a keypress */
    while (!os_GetCSC());
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

