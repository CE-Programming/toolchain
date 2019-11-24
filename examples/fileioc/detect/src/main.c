#include <tice.h>
#include <fileioc.h>

int main(void)
{
    /* search_pos must be NULL to start the search */
    void *search_pos = NULL;
    char *name;
    int8_t y = 0;

    /* First 2 bytes of the LibLoad AppVar, which is known to exist */
    /* Technically a null-terminated string */
    const char search_string[] = { 0xBF, 0xFE, 0x00 };

    /* Clears the homescreen */
    os_ClrHome();

    /* Find all of the variables that start with this string */
    while ((name = ti_Detect(&search_pos, search_string)) != NULL)
    {
        /* Print the name of the variable (Should be LibLoad) */
        os_SetCursorPos(0, y);
        os_PutStrFull(name);

        y++;
    }

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
