#include <ti/screen.h>
#include <ti/getcsc.h>
#include <fileioc.h>

int main(void)
{
    char nameBuffer[10];
    char string[] = "AppVar string";
    uint8_t var;

    /* Clear the homescreen */
    os_ClrHome();

    /* Open a new variable; deleting it if it already exists */
    var = ti_Open("AppVar", "w+");
    if (var == 0)
    {
        return 1;
    }

    /* Write characters to the appvar */
    if (ti_PutC('a', var) == EOF)
    {
        os_PutStrFull("Failed character");
        while (!os_GetCSC());
        return 1;
    }

    /* Write the structure to the appvar */
    if (ti_Write(string, sizeof(string), 1, var) != 1)
    {
        os_PutStrFull("Failed string write");
        while (!os_GetCSC());
        return 1;
    }

    /* Go back to the start of the file */
    if (ti_Rewind(var) == EOF)
    {
        os_PutStrFull("Failed rewind");
        while (!os_GetCSC());
        return 1;
    }

    /* Read character from the appvar */
    if (ti_GetC(var) != 'a')
    {
        os_PutStrFull("Failed character read");
        while (!os_GetCSC());
        return 1;
    }

    /* Read string back to same location */
    if (ti_Read(string, sizeof(string), 1, var) != 1)
    {
        os_PutStrFull("Failed readback");
        while (!os_GetCSC());
        return 1;
    }

    /* Ensure the name of the AppVar is correct */
    ti_GetName(nameBuffer, var);

    /* Ensure that the slot is closed */
    ti_Close(var);
    var = 0;

    os_SetCursorPos(0, 0);
    os_PutStrFull("Appvar: ");
    os_SetCursorPos(0, 8);
    os_PutStrFull(nameBuffer);
    os_SetCursorPos(1, 0);
    os_PutStrFull(string);

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
