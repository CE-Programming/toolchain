#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <intce.h>

/* Function prototypes */
void interrupt isr_timer1(void);
void interrupt isr_on(void);

#define ONE_SECOND         32768/1
#define HALF_SECOND        32768/2
#define QUARTER_SECOND     32768/4

/* Main function */
void main(void) {
    /* Disable the timer so it doesn't run when we don't want it to be running */
    timer_Control = TIMER1_DISABLE;
    
    /* By using the 32768 kHz clock, we can count for exactly a half second here, or a different interval of time */
    timer_1_ReloadValue = timer_1_Counter = HALF_SECOND;
    
    /* Enable the timer, set it to the 32768 kHz clock, enable an interrupt once it reaches 0, and make it count down */
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_0INT | TIMER1_DOWN;
    
    /* Initialize the interrupt handlers */
    int_Initialize();
    
    /* Set the isr_on routine to run when the [ON] key is pressed */
    int_SetVector(ON_IVECT, isr_on);
    
    /* Set the isr_timer1 routine to run when the timer expires */
    int_SetVector(TIMER1_IVECT, isr_timer1);
    
    /* Tell the interrupt controller that the ON flag should be enabled, as with the timer 1 interrupt*/
    int_EnableConfig = INT_ON | INT_TIMER1;
    int_LatchConfig = INT_TIMER1;
    
    /* Interrupts can now generate after this */
    int_Enable();
    
    /* The interrupts will trigger inside this loop */
    while (true);
}

/* Interrupt routine to run when the timer expires */
void interrupt isr_on(void) {
    /* Exit the program if the [ON] key is pressed */
    int_Acknowledge = INT_ON;
    
    /* Reset interrupts and exit */
    int_Reset();
    exit(0);
}

/* Interrupt routine to run when the timer expires */
void interrupt isr_timer1(void) {
    /* Fill the screen with a random color */
    memset_fast(lcd_Ram, randInt(0,255), LCD_SIZE);
    
    /* Must acknowledge that the interrupt occured to clear the flag */
    int_Acknowledge = INT_TIMER1;
}

