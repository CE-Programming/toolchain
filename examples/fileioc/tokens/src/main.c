#include <ti/screen.h>
#include <ti/getcsc.h>
#include <fileioc.h>

int main(void)
{
    uint8_t prgm;
    uint16_t size;
    void *data_ptr;
    int8_t y = 0;

    /* Clears the homescreen */
    os_ClrHome();

    /* Open the "ABC" program for reading */
    prgm = ti_OpenVar("ABC", "r", OS_TYPE_PRGM);
    if (prgm == 0)
    {
        return 1;
    }

    /* Get a pointer to the data in the program */
    data_ptr = ti_GetDataPtr(prgm);
    size = ti_GetSize(prgm);

    while (size && y < 8)
    {
        uint8_t tok_len;

        os_SetCursorPos(0, y);
        os_PutStrFull(ti_GetTokenString(&data_ptr, &tok_len, NULL));

        size -= tok_len;
        y++;
    }

    /* Ensure that the slot is closed */
    ti_Close(prgm);
    prgm = 0;

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
