#include <ti/screen.h>
#include <ti/getcsc.h>
#include <fileioc.h>

static void PrintText(int8_t xpos, int8_t ypos, const char *text)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}

int main(void)
{
    /* Declare some variables */
    const char *oldName = "OldFile";
    const char *newName = "NewFile";
    char nameBuffer[10];
    uint8_t var;
    bool error;

    /* Clear the homescreen */
    os_ClrHome();

    /* Delete both the new and old AppVars if they already exist */
    ti_Delete(oldName);
    ti_Delete(newName);

    error = true;
    do
    {
        /* Create an AppVar with the old name */
        var = ti_Open(oldName, "w");
        if (!var) break;

        ti_GetName(nameBuffer, var);
        PrintText(0, 0, "Old Name: ");
        PrintText(10, 0, nameBuffer);

        /* Rename the old AppVar to the new name */
        ti_Rename(oldName, newName);

        /* Ensure that the slot is closed */
        ti_Close(var);
        var = 0;

        /* Ensure the new name of the file is correct */
        var = ti_Open(newName, "r");
        if (!var) break;

        ti_GetName(nameBuffer, var);
        PrintText(0, 1, "New Name: ");
        PrintText(10, 1, nameBuffer);

        /* Ensure that the slot is closed */
        ti_Close(var);
        var = 0;

        error = false;
    } while (0);

    /* If an error occured, inform the user */
    if (error == true)
    {
        PrintText(0, 2, "An error occured");
    }

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
