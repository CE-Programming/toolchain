#include <tice.h>
#include <fileioc.h>

int main(void)
{
    ti_var_t prgm;
    void *data_ptr;
    uint8_t token_length;
    uint16_t size;
    int8_t y = 0;

    /* Clears the homescreen */
    os_ClrHome();

    /* Closes any open files */
    ti_CloseAll();

    /* Open the "ABC" program for reading */
    prgm = ti_OpenVar("ABC", "r", TI_PRGM_TYPE);
    if (prgm == 0)
    {
        return 1;
    }

    /* Get a pointer to the data in the program */
    data_ptr = ti_GetDataPtr(prgm);
    size = ti_GetSize(prgm);

    while (size && y < 8)
    {
        os_SetCursorPos(0, y);
        os_PutStrFull(ti_GetTokenString(&data_ptr, &token_length, NULL));

        y++;
        size -= token_length;
    }

    /* Waits for a key */
    while (!os_GetCSC());

    /* Closes files */
    ti_CloseAll();

    return 0;
}
