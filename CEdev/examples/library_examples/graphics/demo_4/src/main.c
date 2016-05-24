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

/* Shared libraries */
#include <lib/ce/graphx.h>

/* Put function prototypes here */
void rotate(void);

/* Put globals here */
#define ORG (-50)
#define DEG (6.0)
#define ANG (DEG * M_PI / 180.0)

/* define the verticies for the two rectangles */
float face1[5][2] = {
    { 140, 45  },
    { 240, 45  },
    { 240, 145 },
    { 140, 145 },
    { 140, 45  },
};

float face2[5][2] = {
    { 140 + ORG, 45  - ORG },
    { 240 + ORG, 45  - ORG },
    { 240 + ORG, 145 - ORG },
    { 140 + ORG, 145 - ORG },
    { 140 + ORG, 45  - ORG },
};

/* declare some globals */
float sin_angle,
      cos_angle;

float midx1,
      midy1,
      midx2,
      midy2;

uint8_t loop;

/* Place main code in main */
void main(void) {
	/* Seed the random numbers */
	srand(rtc_Time());
	
	/* Get some main variables set up */
	sin_angle = sin(ANG);
	cos_angle = cos(ANG);
	midx1 = (face1[0][0] + face1[1][0]) / 2.0;
	midy1 = (face1[1][1] + face1[2][1]) / 2.0;
	midx2 = (face2[0][0] + face2[1][0]) / 2.0;
	midy2 = (face2[1][1] + face2[2][1]) / 2.0;
	
	/* Start the graphics routines */
	gfx_Begin(gfx_8bpp);
	gfx_SetDraw(gfx_buffer);
	
	/* Loop until a key is pressed */
	while (!os_GetCSC()) {
		
		/* Change the color of the cube depending on loop (mod 16) */
		if (!((loop++) & 0xF)) {
			gfx_SetColor(rand() & 0xFE);
		}
		
		/* Call the rotation code */
		rotate();
		
		/* Swap the buffer with the screen */
		gfx_SwapDraw();
	}
	
	/* Clean up the program */
	gfx_End();
	prgm_CleanUp();
}

/* Rotation code */
void rotate(void) {
	uint8_t i;
	float tmp1, tmp2;
	
	/* Clear out the old rectangles */
	gfx_FillScreen(gfx_white);
	
	/* Compute the new face places */
	for (i=0; i<5; i++) {
		tmp1 = face1[i][0] - midx1;
		tmp2 = face1[i][1] - midy1;
		
		face1[i][0] = midx1 + (tmp1 * cos_angle) - (tmp2 * sin_angle);
		face1[i][1] = midy1 + (tmp1 * sin_angle) + (tmp2 * cos_angle);
		
		tmp1 = face2[i][0] - midx2;
		tmp2 = face2[i][1] - midy2;
		
		face2[i][0] = midx2 + (tmp1 * cos_angle) - (tmp2 * sin_angle);
		face2[i][1] = midy2 + (tmp1 * sin_angle) + (tmp2 * cos_angle);
	}
	
	/* Draw the cube itself */
	for (i=0; i<4; i++) {
		gfx_Line(face1[i][0], face1[i][1], face1[i+1][0], face1[i+1][1]);
		gfx_Line(face2[i][0], face2[i][1], face2[i+1][0], face2[i+1][1]);
		gfx_Line(face1[i][0], face1[i][1], face2[ i ][0], face2[ i ][1]);
	}
}