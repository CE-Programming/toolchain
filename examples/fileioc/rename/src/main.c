#include <tice.h>
#include <fileioc.h>

void PrintText(int8_t xpos, int8_t ypos, const char *text);

int main(void)
{
    /* Declare some variables */
    const char *oldName = "OldFile";
    const char *newName = "NewFile";
    char nameBuffer[10];
    ti_var_t file;
    bool error = true;

    /* Clear the homescreen */
    os_ClrHome();

    /* Close any previously open files */
    ti_CloseAll();

    /* Delete both the new and old files if they already exist */
    ti_Delete(oldName);
    ti_Delete(newName);

    do
    {
        /* Create a file with the old name */
        file = ti_Open(oldName, "w");
        if (!file) break;

        ti_GetName(nameBuffer, file);
        PrintText(0, 0, "Old Name: ");
        PrintText(10, 0, nameBuffer);

        /* Close the old file */
        ti_CloseAll();

        /* Rename the old file to the new file name */
        ti_Rename(oldName, newName);

        /* Ensure the new name of the file is correct */
        file = ti_Open(newName, "r");
        if (!file) break;

        ti_GetName(nameBuffer, file);
        PrintText(0, 1, "New Name: ");
        PrintText(10, 1, nameBuffer);

        error = false;
    } while (0);

    /* Close all open files */
    ti_CloseAll();

    /* If an error occured, inform the user */
    if (error == true)
    {
        PrintText(0, 2, "An error occured");
    }

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}

/* Draw text on the homescreen at the given X/Y location */
void PrintText(int8_t xpos, int8_t ypos, const char *text)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
