#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>

/* Function Prototypes */
void fill_screen(uint8_t color);

void main(void) {
    /* Key varaible */
    kb_key_t key;
    
    /* Loop until 2nd is pressed */
    do {
        /* Update kb_Data */
        kb_Scan();
		
        /* Load group 7 registers */
        key = kb_Data[7];
        
        switch (key) {
            case kb_Down:           /* Change screen color to black */
                fill_screen(0x00);
                break;
            case kb_Right:          /* Change screen color to red */
                fill_screen(0xE0);
                break;
            case kb_Up:             /* Change screen color to white */
                fill_screen(0xFF);
                break;
            case kb_Left:           /* Change screen color to a different red */
                fill_screen(0xC0);
                break;
            default:
                break;
        }
    } while (kb_Data[1] != kb_2nd);
}

/* Simple way to fill the screen with a given color */
void fill_screen(uint8_t color) {
    memset(lcd_Ram, color, LCD_SIZE);
}

