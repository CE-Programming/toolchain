#include <tice.h>
#include <fileioc.h>

int main(void)
{
    /* search_pos must be NULL to start the search */
    void *search_pos = NULL;
    char *name;
    int8_t y = 0;
    uint8_t type;

    /* First couple bytes of the LibLoad AppVar, which is known to exist */
    /* Technically is a null-terminated string, if an odd looking one */
    const char search_string[] = { 0xBF, 0xFE, 0x00 };

    /* Clear the homescreen */
    os_ClrHome();

    /* Find all of the variables that start with this string */
    while ((name = ti_DetectAny(&search_pos, search_string, &type)) != NULL)
    {
        if (type == TI_APPVAR_TYPE)
        {
            /* Print the name of the variable (Should be LibLoad) */
            os_SetCursorPos(0, y);
            os_PutStrFull(name);

            y++;
        }
    }

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
