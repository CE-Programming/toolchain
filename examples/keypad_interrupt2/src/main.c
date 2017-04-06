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

/* Interrupt library */
#include <intce.h>

/* CE Keypad C Library */
#include <lib/keypadc.h>

/* Function prototypes */
void interrupt isr_on(void);
void interrupt isr_keyboard(void);

/* Global Flag */
uint8_t exit_loop = false;

/* Main Function */
void main(void) {
    /* Initialize the interrupt handlers */
    int_Initialize();
    
    /* Set the isr_on routine to run when the [ON] key is pressed */
    int_SetVector(ON_IVECT, isr_on);
    int_SetVector(KEYBOARD_IVECT, isr_keyboard);
    
    /* Tell the interrupt controller that the ON flag should latch and be enabled */
    int_EnableConfig = INT_ON | INT_KEYBOARD;
    kb_EnableInt = KB_MODE_1_PRESS;
    
    /* Configure the keypad to be continously scanning */
    kb_SetMode(MODE_1_INDISCRIMINATE);
    
    /* Interrupts can now generate after this */
    int_Enable();
    
    /* Wait for the [ON] key to be pressed */
    while( !exit_loop );
    
    /* Reset the interrupt handler and cleanup the program */
    int_Reset();
    kb_Reset();
    prgm_CleanUp();
}

/* Interrupt routine to run when the [ON] key is pressed */
void interrupt isr_on(void) {
    /* Exit the "infinite" loop */
    exit_loop = true;
    
    /* Must acknowledge that the interrupt occured to clear the flag */
    int_Acknowledge = INT_ON;
}

void interrupt isr_keyboard(void) {
    /* Fill the screen with a fun color */
    memset_fast(lcd_Ram, randInt(0,255), LCD_SIZE);
    
    /* Must acknowledge that the interrupt occured to clear the flag */
    int_Acknowledge = INT_KEYBOARD;
    /* Acknowledge in the keypad controller (This is required for mode 1) */
    kb_IntAcknowledge = KB_MODE_1_PRESS;
}
