#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 10
#define BUFFER_SIZE 20

/* Function prototypes */
void print(char *text, uint8_t xpos, uint8_t ypos);

/* Main Function */
void main(void) {
    const char prompt[] = "What is N? ";
    char input[INPUT_SIZE];
    char response[BUFFER_SIZE];
    
    /* Clear the homescreen */
    os_ClrHome();
    
    /* Get an input string from the user */
    os_GetStringInput(prompt, input, sizeof input);

    /* Build the user response */
    strcpy(response, "N is ");
    strcat(response, input);
    
    /* Clear the homescreen */
    os_ClrHome();
    
    /* Print the message back to the user */
    print(response, 0, 0);
    
    /* Wait for a key press */
    while (!os_GetCSC());
}

/* Draw text on the homescreen at the given X/Y location */
void print(char *text, uint8_t xpos, uint8_t ypos) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

