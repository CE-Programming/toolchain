#include <ti/screen.h>
#include <ti/getkey.h>
#include <fileioc.h>

int main(void)
{
    /* Must be NULL to start the search */
    void *search_pos = NULL;

    /* Clear the homescreen */
    os_ClrHome();

    for (;;)
    {
        uint8_t type;
        const char *name = ti_DetectAny(&search_pos, "", &type);

        if (name == NULL)
        {
            break;
        }

        /* Only show programs */
        if (type != OS_TYPE_PROT_PRGM && type != OS_TYPE_PRGM)
        {
            continue;
        }

        /* System programs have first character < 'A' */
        if (name[0] < 'A')
        {
            continue;
        }

        /* Print the name of the program */
        os_PutStrFull(name);
        os_NewLine();
    }

    /* Waits for a key */
    os_GetKey();

    return 0;
}
