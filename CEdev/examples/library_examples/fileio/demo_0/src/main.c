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
const char nameAppVar[] = "AppVar";

typedef struct myData {
    uint8_t settings_name[15];
    uint8_t var1;
    uint8_t var2;
} myData_t;

myData_t dataStruct;

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

/* Main Function */
void main(void) {
	ti_var_t myAppVar;
	int x;
    
	strcpy(dataStruct.settings_name, "My Settings");
	dataStruct.var1 = 10;
	dataStruct.var2 = 20;
    
	/* Close any files that may be open already */
	ti_CloseAll();
    
	/* Open a new variable; deleting it if it already exists */
	myAppVar = ti_Open(nameAppVar,"w");

	/* Make sure we opened okay */
	if (!myAppVar)								goto err;
    
	/* Write the structure to the appvar */
	if ((ti_Write(&dataStruct, sizeof(myData_t), 1, myAppVar)) != 1)	goto err;
    
	/* Let's read it just to make sure we wrote it correctly */
	if ((ti_Rewind(myAppVar) == -1))					goto err;
	
	if ((ti_Read(&dataStruct, sizeof(myData_t), 1, myAppVar)) != 1)		goto err;
    
	/* Make sure we read these varaibles correctly too */
	if (dataStruct.var1 != 10 && dataStruct.var2 != 20)			goto err;
    
	printText(0,0,"Read was successful");
	goto noerr;

err:
	printText(0,0,"An error occured");
noerr:
  
	/* Get the scan codes */
	while( !os_GetCSC() );
    
	ti_CloseAll();
	prgm_CleanUp();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
	os_SetCursorPos(ypos, xpos);
	os_PutStrFull(text);
}
