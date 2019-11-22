/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers (recommended) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>

/* Put your function prototypes here */
void begin();
void end();
bool step();
void draw();

/* Put all your globals here */
bool partial_redraw;

void main() {
    begin(); // No rendering allowed!
    gfx_Begin();
    gfx_SetDrawBuffer(); // Draw to the buffer to avoid rendering artifats

    while (step()) { // No rendering allowed in step!
        if (partial_redraw) // Only want to redraw part of the previous frame?
            gfx_BlitScreen(); // Copy previous frame as a base for this frame
        draw(); // As little non-rendering logic as possible
        gfx_SwapDraw(); // Queue the buffered frame to be displayed
    }

    gfx_End();
    end();
}

/* Put other functions here */
void begin() {
    /* Implement me! */
}

void end() {
    /* Implement me! */
}

bool step() {
    /* Implement me! */
}

void draw() {
    /* Implement me! */
}
