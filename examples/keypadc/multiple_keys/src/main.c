#include <ti/screen.h>
#include <keypadc.h>

/* Function prototypes */
void PrintText(int8_t xpos, int8_t ypos, const char *text);

int main(void)
{
    /* Key variable */
    kb_key_t key;
    const char *erase_string = "     ";

    /* Clear the homescreen */
    os_ClrHome();

    /* Loop until 2nd is pressed */
    do
    {
        /* Update kb_Data */
        kb_Scan();

        key = kb_Data[7];

        /* Print the current arrow key input */
        PrintText(0, 0, key & kb_Down ? "Down" : erase_string);

        PrintText(0, 1, key & kb_Up ? "Up" : erase_string);

        PrintText(0, 2, key & kb_Left ? "Left" : erase_string);

        PrintText(0, 3, key & kb_Right ? "Right" : erase_string);

    } while (kb_Data[1] != kb_2nd);

    return 0;
}

/* Draw text on the homescreen at the given X/Y location */
void PrintText(int8_t xpos, int8_t ypos, const char *text)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
