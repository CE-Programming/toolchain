#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <intce.h>
#include <keypadc.h>

/* Function prototypes */
void interrupt isr_on(void);
void interrupt isr_keyboard(void);

/* Global Flag */
uint8_t exit_loop = false;

void main(void) {
    /* Initialize the interrupt hardware */
    int_Initialize();
    
    /* Set the isr_on routine to run when the [ON] key is pressed */
    int_SetVector(ON_IVECT, isr_on);
    int_SetVector(KEYBOARD_IVECT, isr_keyboard);
    
    /* Tell the interrupt controller that the ON flag to be enabled */
    int_EnableConfig = INT_ON | INT_KEYBOARD;
    kb_EnableInt = KB_DATA_CHANGED;
    
    /* Configure the keypad to be continously scanning */
    kb_SetMode(MODE_3_CONTINUOUS);
    
    /* Interrupts can now generate after this */
    int_Enable();
    
    /* Wait for the [ON],[clear], or [enter] keys to be pressed */
    while (!exit_loop);
    
    /* Reset the interrupt handler and keypad */
    int_Reset();
    kb_Reset();
}

/* Interrupt routine to run when the [ON] key is pressed */
void interrupt isr_on(void) {
    /* Exit the "infinite" loop */
    exit_loop = true;
    
    /* Must acknowledge that the interrupt occured to clear the flag */
    int_Acknowledge = INT_ON;
}

void interrupt isr_keyboard(void) {
    /* Read the keypad data */
    kb_key_t key = kb_Data[kb_group_6];
    
    /* If [enter] or [clear] are pressed, set the flag */
    if (key & (kb_Enter | kb_Clear)) {
        exit_loop = true;
    }
    
    /* Must acknowledge that the interrupt occured to clear the flag */
    int_Acknowledge = INT_KEYBOARD;
    /* Acknowledge in the keypad controller (Not technically required because interrupt controller handles signal) */
    kb_IntAcknowledge = KB_DATA_CHANGED;
}

