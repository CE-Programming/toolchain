#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <intce.h>

/* Function prototypes */
void interrupt isr_on(void);

/* Global status flag */
bool exit_loop = false;

/* Main function */
void main(void) {
    /* Print a little string -- NOTE: OS routines don't work well when interrupts are enabled */
    os_ClrHome();
    os_SetCursorPos(0, 0);
    os_PutStrFull("Press ON");
    
    /* Initialize the interrupt handlers */
    int_Initialize();
    
    /* Set the isr_on routine to run when the [ON] key is pressed */
    int_SetVector(ON_IVECT, isr_on);
    
    /* Tell the interrupt controller that the ON interrupt should be enabled */
    int_EnableConfig = INT_ON;
    
    /* Interrupts can now generate after this */
    int_Enable();
    
    /* Wait for the [ON] key to be pressed */
    while (!exit_loop);
    
    /* Reset the interrupt handler and cleanup the program */
    int_Reset();
}

/* Interrupt routine to run when the [ON] key is pressed */
void interrupt isr_on(void) {
    /* Exit the "infinite" loop */
    exit_loop = true;
    
    /* Must acknowledge that the interrupt occured to clear the flag */
    int_Acknowledge = INT_ON;
}

