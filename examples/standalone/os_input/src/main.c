#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <tice.h>

/* Make sure to adjust those sizes according to your usage! */
#define INPUT_SIZE  10
#define RESP_SIZE   20

/* Draw text on the homescreen at the given X/Y location */
void print(const char* text, uint8_t xpos, uint8_t ypos) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

void main(void) {
    char inputBuffer[INPUT_SIZE];
    char response[RESP_SIZE];

    /* Clear the homescreen */
    os_ClrHome();

    /* Ask the user to type a string, which gets stored in `inputBuf` */
    os_GetStringInput("What is N? ", inputBuffer, INPUT_SIZE);

    /* Build the user response */
    sprintf(response, "N is %s.", inputBuffer);

    /* Clear the homescreen and display the built response */
    os_ClrHome();
    print(response, 0, 0);

    /* Wait for a key press before quitting */
    while (!os_GetCSC());
}
