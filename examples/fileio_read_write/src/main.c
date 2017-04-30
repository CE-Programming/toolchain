#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fileioc.h>

/* Declare some variables */
const char *appvarName = "AppVar";

typedef struct {
    char name[15];
    uint8_t var1;
    uint8_t var2;
} data_t;

data_t data;

#define VAR1_VALUE 10
#define VAR2_VALUE 20

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

/* Main Function */
void main(void) {
    ti_var_t myAppVar;
    int x;
    
    /* Declare some varaible values */
    strcpy(data.name, "My Data");
    data.var1 = VAR1_VALUE;
    data.var2 = VAR2_VALUE;
    
    /* Close any files that may be open already */
    ti_CloseAll();
    
    /* Open a new variable; deleting it if it already exists */
    myAppVar = ti_Open(appvarName, "w");

    /* Make sure we opened okay */
    if (!myAppVar)                                          goto err;

    /* Write the structure to the appvar */
    if (ti_Write(&data, sizeof(data_t), 1, myAppVar) != 1)  goto err;

    /* Go back to the start of the file */
    if (ti_Rewind(myAppVar) == EOF)                         goto err;

    /* Let's read it just to make sure we wrote it correctly */
    if (ti_Read(&data, sizeof(data_t), 1, myAppVar) != 1)   goto err;

    /* Make sure we read these varaibles correctly too */
    if (data.var1 != VAR1_VALUE && data.var2 != VAR2_VALUE) goto err;
    
    printText(0, 0, "Read was successful");
    goto noerr;

err:
    printText(0, 0, "An error occured");
noerr:
  
    /* Pause */
    while (!os_GetCSC());
    
    /* Close all open files */
    ti_CloseAll();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
