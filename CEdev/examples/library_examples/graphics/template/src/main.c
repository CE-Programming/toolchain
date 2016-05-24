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

/* C CE Graphics library */
#include <lib/ce/graphx.h>

/* Put function prototypes here */

/* Put all your code here */
void main(void) {
	gfx_Begin(gfx_8bpp);
	
	/* Place program code here */
	
	gfx_End();
	prgm_CleanUp();
}
