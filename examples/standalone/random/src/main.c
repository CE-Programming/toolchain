#include <stdlib.h>
#include <ti/getcsc.h>
#include <ti/screen.h>
#include <sys/rtc.h>
#include <sys/lcd.h>
#include <sys/util.h>

int main(void)
{
    /* Get pointers to memory-mapped screen */
    uint32_t *lcd_Ram_i;
    uint32_t *lcd_Ram_end = (uint32_t*)((uintptr_t)lcd_Ram + LCD_SIZE);

    /* Set the random seed based off the real time clock */
    srand(rtc_Time());

    /* Fill the screen with random data */
    for (lcd_Ram_i = (uint32_t*)lcd_Ram; lcd_Ram_i < lcd_Ram_end; ++lcd_Ram_i)
    {
        *lcd_Ram_i = random();
    }

    /* Waits for a key */
    while (!os_GetCSC());

    return 0;
}
