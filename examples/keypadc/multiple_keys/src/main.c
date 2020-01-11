#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

void main(void) {
    /* Key variable */
    kb_key_t key;
    const char *erase_string = "     ";

    /* Clear the homescreen */
    os_ClrHome();

    /* Loop until 2nd is pressed */
    do {

        /* Update kb_Data */
        kb_Scan();

        key = kb_Data[7];

        /* Print the current arrow key input */
        if (key & kb_Down) {
            printText(0, 0, "Down");
        } else {
            printText(0, 0, erase_string);
        }
        if (key & kb_Up) {
            printText(0, 1, "Up");
        } else {
            printText(0, 1, erase_string);
        }
        if (key & kb_Left) {
            printText(0, 2, "Left");
        } else {
            printText(0, 2, erase_string);
        }
        if (key & kb_Right) {
            printText(0, 3, "Right");
        } else {
            printText(0, 3, erase_string);
        }

    } while (kb_Data[1] != kb_2nd);
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
