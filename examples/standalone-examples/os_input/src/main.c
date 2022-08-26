#include <ti/getcsc.h>
#include <ti/screen.h>
#include <stdio.h>

/* Set maximum size of input and output buffers */
#define INPUT_SIZE  10
#define RESP_SIZE   20

int main(void)
{
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
    os_PutStrFull(response);

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
