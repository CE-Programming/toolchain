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

/* CE Keypad C Library */
#include <lib/ce/keypadc.h>

/* Function prototypes */
void printText(int8_t xpos, int8_t ypos, const char *text);

/* Main Function */
void main(void) {
	/* Key varaible */
	kb_key_t key;
	char erase_string[] = "     ";
	
	/* Loop until 2nd is pressed */
	while(kb_ScanGroup(kb_group_1) != kb_2nd) {
		key = kb_ScanGroup(kb_group_7);

		/* Print the current arrow key input */
		if(key & kb_Down) {
			printText(0,0,"Down");
		} else {
			printText(0,0,erase_string);
		}
		if(key & kb_Up) {
			printText(0,1,"Up");
		} else {
			printText(0,1,erase_string);
		}
		if(key & kb_Left) {
			printText(0,2,"Left");
		} else {
			printText(0,2,erase_string);
		}
		if(key & kb_Right) {
			printText(0,3,"Right");
		} else {
			printText(0,3,erase_string);
		}
	}
	prgm_CleanUp();
}

/* Draw text on the homescreen at the given X/Y location */
void printText(int8_t xpos, int8_t ypos, const char *text) {
	os_SetCursorPos(ypos, xpos);
	os_PutStrFull(text);
}
