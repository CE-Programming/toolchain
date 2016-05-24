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

/* Shared library headers -- depends on which ones you wish to use */
#include <lib/ce/fileioc.h>

/* Declare some strings and variables */
const char prgmName[] = "ABC";

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

/* Main Function */
void main(void) {
	ti_var_t myProgram;
	uint8_t *data_ptr;
	uint8_t token_length;
	
	/* Close any files that may be open already */
	ti_CloseAll();
    
	/* Open a new variable; deleting it if it already exists */
	myProgram = ti_OpenVar(prgmName,"r",ti_Program);
    
	/* Make sure we opened okay */
	if (!myProgram) goto err;

	data_ptr = ti_GetDataPtr( myProgram );
	printText( 0, 0, ti_GetTokenString( &data_ptr, NULL, NULL ) );
	printText( 0, 1, ti_GetTokenString( &data_ptr, NULL, NULL ) );
	
err:	
	/* Wait for a key */
	while( !os_GetCSC() );
    
	ti_CloseAll();
	prgm_CleanUp();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
	os_SetCursorPos(ypos, xpos);
	os_PutStrFull(text);
}
