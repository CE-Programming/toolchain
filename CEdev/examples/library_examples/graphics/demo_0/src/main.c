/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Shared libraries */
#include <lib/ce/graphx.h>

/* Put function prototypes here */
void print_string_centered(const char *str);

/* Put all your code here */
void main(void) {
	unsigned x;
	uint8_t y;
	const char msg[] = "Hello World!";
	
	/* Seed the random numbers */
	srand( rtc_Time() );
	
	/* Initialize the 8bpp graphics */
	gfx_Begin( gfx_8bpp );
	
	/* Fill the screen black */
	gfx_FillScreen( gfx_black );
	
	/* Set the random text color */
	gfx_SetTextFGColor( randInt(1,255) );
	
	/* Print a string centered on the screen */
	print_string_centered( msg );
	
	/* Wait for a key to be pressed */
	while( !os_GetCSC() );
	
	/* Close the graphics and return to the OS */
	gfx_End();
	prgm_CleanUp();
}

/* Prints a screen centered string */
void print_string_centered(const char *str) {
	gfx_PrintStringXY(str, (gfx_lcdWidth-gfx_GetStringWidth(str)) / 2, (gfx_lcdHeight-gfx_FontHeight()) / 2);
}
