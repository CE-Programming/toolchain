#include <lcddrvce.h>
#include <sys/lcd.h>
#include <ti/getcsc.h>
#include <stdint.h>
#include <string.h>

/* Function Prototypes */
void DrawGradient(uint24_t gradientStep);

int main(void)
{
    /* Initialize LCD driver */
    lcd_Init();

    /* Set uniform gamma profile */
    lcd_SetUniformGamma();
    /* Switch RAM access to SPI and display mode to MCU */
    lcd_SetRamInterface(LCD_RAM_SPI | LCD_DM_MCU);
    /* Set 18bpp pixel format */
    lcd_SetPixelFormat(LCD_SPI_18BPP | LCD_RGB_DEFAULT);

    /* Start RAM write command */
    lcd_StartPixelWrite();

    /* Generate and display gradient patterns */
    DrawGradient(0x040404);
    DrawGradient(0x000004);
    DrawGradient(0x000400);
    DrawGradient(0x040000);

    /* Wait for a keypress */
    while (!os_GetCSC());

    /* Restore default LCD settings */
    lcd_SetDefaultGamma();
    lcd_SetRamInterface(LCD_RAMCTRL1_DEFAULT);
    lcd_SetPixelFormat(LCD_COLMOD_DEFAULT);

    /* Cleanup LCD driver */
    lcd_Cleanup();

    return 0;
}

void DrawGradient(uint24_t gradientStep)
{
    /* Generate test pattern in line buffer */
    static uint24_t lineBuffer[LCD_WIDTH];
    uint24_t pixel = 0;
    size_t index = 0;
    while (index < LCD_WIDTH)
    {
        lineBuffer[index++] = pixel;
        lineBuffer[index++] = pixel;
        lineBuffer[index++] = pixel;
        lineBuffer[index++] = pixel;
        lineBuffer[index++] = pixel;
        pixel += gradientStep;
    }

    /* Send the line buffer to 1/4 of the display */
    for (uint8_t row = 0; row < LCD_HEIGHT / 4; row++)
    {
        lcd_SendParamsRaw(sizeof(lineBuffer), lineBuffer);
    }
}
