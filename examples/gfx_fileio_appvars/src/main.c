#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <debug.h>

#include <graphx.h>
#include <fileioc.h>

/* Include the sprite data */
#include "gfx/all_gfx.h"
#include "gfx/var_gfx.h"

void main(void) {
    uint8_t i;
    
    /* We don't really care about the type of data here */
    void *data;
    
    /* The type used for keeping track of the appvar we open */
    ti_var_t appvar;
    
    /* Close any open files */
    ti_CloseAll();
    
    /* We used convpng to store the 'ubuntu' image into the */
    /* appvar 'var_gfx'. This command will open that appvar */
    /* Next we get a pointer to the data inside the appvar  */
    /* This is a direct pointer to the images               */
    appvar = ti_Open("var_gfx", "r");
    data = ti_GetDataPtr(appvar);
    
    /* Now fixup the pointers to the actual sprites */
    for (i = 0; i < var_gfx_num; i++) {
        var_gfx[i] += (int)data;
    }
    
    /* Initialize the 8bpp graphics */
    gfx_Begin(gfx_8bpp);
    
    /* Set up the palette for the sprite */
    gfx_SetPalette(all_gfx_pal, sizeof all_gfx_pal, 0);
    
    /* Fill the screen with color index 0 */
    gfx_FillScreen(0);
    
    /* Draw the sprites directly from the appvar */
    gfx_Sprite(ubuntu, LCD_WIDTH/2 - 16, LCD_HEIGHT/2 - 16);
    gfx_Sprite(mint, LCD_WIDTH/2 + 16, LCD_HEIGHT/2 - 16);
    
    /* Wait for a key to be pressed */
    while (!os_GetCSC());
    
    /* Close the graphics */
    gfx_End();
}

