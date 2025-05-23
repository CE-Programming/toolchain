#include <lcddrvce.h>
#include <graphx.h>
#include <sys/lcd.h>
#include <ti/getcsc.h>
#include <stdint.h>
#include <string.h>

#define HALF_LCD_WIDTH (LCD_WIDTH / 2)
#define HALF_LCD_HEIGHT (LCD_HEIGHT / 2)

/* Function Prototypes */
void PrintCentered(const char *str, unsigned int border);
void QuarterResFillScreen(uint8_t color);
void QuarterResSwapDraw(void);
void SetHalfResMode(bool enable);

int main(void)
{
    /* Initialize GraphX first, because it sets LCD timing */
    gfx_Begin();
    
    /* Set half-resolution mode */
    SetHalfResMode(true);

    /* Set clipping to an 160x120 area that draws to every second line of the half-res buffer */
    gfx_SetClipRegion(0, 0, HALF_LCD_WIDTH - 1, HALF_LCD_HEIGHT - 1);
    gfx_SetDrawBuffer();

    unsigned int border = 2;
    int dir = 1;

    /* Wait for a keypress */
    while (!os_GetCSC())
    {
        /* Clear the screen, gfx_FillScreen covers too much area so use this instead */
        QuarterResFillScreen(255);
        
        /* Print the message on the screen */
        PrintCentered("Hello, World!", border);

        /* Swap buffers and fill in every second line */
        QuarterResSwapDraw();

        /* Change the border size for the next frame */
        border += dir;
        if (border <= 2 || border >= 25)
        {
            dir = -dir;
        }
    }

    /* Ensure one empty frame is fully displayed to make the transition to full-res clean */
    gfx_FillScreen(255);
    gfx_SwapDraw();
    gfx_FillScreen(255);
    gfx_SwapDraw();

    /* Restore normal resolution mode */
    SetHalfResMode(false);

    /* Wait for the second empty frame to display */
    gfx_Wait();

    /* Deinitialize GraphX */
    gfx_End();

    return 0;
}

/* Prints a quarter-res screen centered string */
void PrintCentered(const char *str, unsigned int border)
{
    unsigned int width = gfx_GetStringWidth(str);
    gfx_PrintStringXY(str,
                      (HALF_LCD_WIDTH - width) / 2,
                      (HALF_LCD_HEIGHT - 8) / 2);
    gfx_Circle(HALF_LCD_WIDTH / 2, HALF_LCD_HEIGHT / 2, width / 2 + border);
}

/* Fills the drawable area of a quarter-res screen */
void QuarterResFillScreen(uint8_t color)
{
    uint8_t oldColor = gfx_SetColor(color);
    gfx_FillRectangle_NoClip(0, 0, HALF_LCD_WIDTH, HALF_LCD_HEIGHT);
    gfx_SetColor(oldColor);
}

/* Copies the rendered lines to the unrendered lines before swapping the buffer */
void QuarterResSwapDraw(void)
{
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 0, 0, HALF_LCD_WIDTH, 0, HALF_LCD_WIDTH, HALF_LCD_HEIGHT);
    gfx_SwapDraw();
}

void SetHalfResMode(bool enable)
{
    typedef struct lcd_timing
    {
        uint32_t : 2;
        uint32_t PPL : 6;
        uint32_t HSW : 8;
        uint32_t HFP : 8;
        uint32_t HBP : 8;

        uint32_t LPP : 10;
        uint32_t VSW : 6;
        uint32_t VFP : 8;
        uint32_t VBP : 8;

        uint32_t PCD_LO : 5;
        uint32_t CLKSEL : 1;
        uint32_t ACB : 5;
        uint32_t IVS : 1;
        uint32_t IHS : 1;
        uint32_t IPC : 1;
        uint32_t IOE : 1;
        uint32_t : 1;
        uint32_t CPL : 10;
        uint32_t BCD : 1;
        uint32_t PCD_HI : 5;
    } lcd_timing_t;

    typedef struct res_settings
    {
        uint8_t frctrl;
        uint8_t bp;
        uint16_t xe;
        uint8_t tfa;
        uint8_t ramctrl1;
        lcd_timing_t timing;
    } res_settings_t;

    static res_settings_t settings[2] =
    {
        {
            /* Default ST7789 settings */
            .frctrl = LCD_FRCTRL_DEFAULT,
            .bp = LCD_BP_DEFAULT,
            .xe = LCD_WIDTH - 1,
            .tfa = 0,
            .ramctrl1 = LCD_RAMCTRL1_DEFAULT
        },
        {
            /* With the following ST7789 timing:
             * Refreshes LCD in at most 16.51 ms after VSYNC, assuming worst case 9.5 MHz clock
             * Waits at least 3.42 ms after VSYNC to read LCD memory, assuming worst case 10.5 MHz clock
             */
            .frctrl = LCD_RTN_378 | LCD_NL_DEFAULT, /* 378 clocks per line */
            .bp = 95, /* 95 lines of back porch */
            .xe = HALF_LCD_WIDTH - 1,
            .tfa = HALF_LCD_WIDTH,
            .ramctrl1 = LCD_DM_VSYNC | LCD_RAM_DEFAULT,
            /* With the following PL111 timing:
             * Refreshes LCD at 60 Hz = 24 MHz / (800*250*2), a VSYNC period of 16.67 ms
             * Outputs 38400 pixels to LCD memory within the first 3.40 ms after VSYNC
             */
            .timing =
            {
                .PPL = 768 / 16 - 1, /* 768 pixels per line */
                .HSW = 1 - 1,
                .HFP = (800 - 768 - 1 - 1) - 1, /* 800 total clocks per line */
                .HBP = 1 - 1,
                .LPP = HALF_LCD_WIDTH * LCD_HEIGHT / 768, /* 50 lines */
                .VSW = 1 - 1,
                .VFP = 250 - (HALF_LCD_WIDTH * LCD_HEIGHT / 768) - 1, /* 250 total lines */
                .VBP = 0,
                .PCD_LO = (2 - 2) & 0x1F, /* clock divisor of 2 */
                .CLKSEL = 0,
                .ACB = 0,
                .IVS = 1,
                .IHS = 1,
                .IPC = 1,
                .IOE = 1,
                .CPL = 768 - 1,
                .BCD = 0,
                .PCD_HI = (2 - 2) >> 5
            }
        }
    };

    const res_settings_t *p = &settings[enable];

    /* Initialize LCD driver */
    lcd_Init();

    /* Set clocks per line */
    lcd_SetNormalFrameRateControl(p->frctrl);
    /* Set back porch */
    lcd_SetNormalBackPorchControl(p->bp);
    /* Set horizontal output window */
    lcd_SetColumnAddress(0, p->xe);
    /* Set fixed left scroll area */
    lcd_SetScrollArea(p->tfa, LCD_WIDTH - p->tfa, 0);
    /* Set starting vertical scroll address to 0 */
    lcd_SetScrollAddress(0);    
    /* Set display mode */
    lcd_SetRamInterface(p->ramctrl1);
    /* Set interlace mode */
    lcd_SetInterlacedMode(enable);

    /* Save old display timing when enabling */
    if (enable)
    {
        memcpy(&settings[0].timing, (const void *)&lcd_Timing0, sizeof(settings[0].timing));
    }
    /* Set display timing */
    memcpy((void *)&lcd_Timing0, &p->timing, sizeof(p->timing));

    /* Cleanup LCD driver */
    lcd_Cleanup();
}
