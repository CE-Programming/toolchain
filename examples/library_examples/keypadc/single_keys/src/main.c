#include <sys/lcd.h>
#include <keypadc.h>
#include <string.h>

/* Function Prototypes */
void FillScreen(uint8_t color);

int main(void)
{
    /* Key variable */
    kb_key_t key;

    /* Loop until 2nd is pressed */
    do
    {
        /* Update kb_Data */
        kb_Scan();

        /* Load group 7 registers */
        key = kb_Data[7];

        switch (key)
        {
            case kb_Down:           /* Change screen color to black */
                FillScreen(0x00);
                break;

            case kb_Right:          /* Change screen color to red */
                FillScreen(0xE0);
                break;

            case kb_Up:             /* Change screen color to white */
                FillScreen(0xFF);
                break;

            case kb_Left:           /* Change screen color to a different red */
                FillScreen(0xC0);
                break;

            default:
                break;
        }

    } while (kb_Data[1] != kb_2nd);

    return 0;
}

/* Simple way to fill the screen with a given color */
void FillScreen(uint8_t color)
{
    memset((void*)lcd_Ram, color, LCD_SIZE);
}
