#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <lcddrvce.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

#include "graphics.h"

/* cube drawing code */

#define ORG (-50.0f)
#define DEG (6.0f)
#define ANG (DEG * M_PI / 180.0f)

typedef struct {
    float sin_ang;
    float cos_ang;
    float midx1;
    float midy1;
    float midx2;
    float midy2;
} cube_t;

static float face1[4][2] = {
    { 140.0f,  45.0f },
    { 240.0f,  45.0f },
    { 240.0f, 145.0f },
    { 140.0f, 145.0f },
};

static float face2[4][2] = {
    { 140.0f + ORG,  45.0f - ORG },
    { 240.0f + ORG,  45.0f - ORG },
    { 240.0f + ORG, 145.0f - ORG },
    { 140.0f + ORG, 145.0f - ORG },
};

/* Cube rotation */
void rotate(cube_t *cube) {
    static uint8_t drawnTimes = 0;
    /* Compute the new vertex coordinates */
    for (uint8_t i = 0; i < 4; ++i) {
        float tmp1, tmp2;

        tmp1 = face1[i][0] - cube->midx1;
        tmp2 = face1[i][1] - cube->midy1;

        face1[i][0] = cube->midx1 + (tmp1 * cube->cos_ang) - (tmp2 * cube->sin_ang);
        face1[i][1] = cube->midy1 + (tmp1 * cube->sin_ang) + (tmp2 * cube->cos_ang);

        tmp1 = face2[i][0] - cube->midx2;
        tmp2 = face2[i][1] - cube->midy2;

        face2[i][0] = cube->midx2 + (tmp1 * cube->cos_ang) - (tmp2 * cube->sin_ang);
        face2[i][1] = cube->midy2 + (tmp1 * cube->sin_ang) + (tmp2 * cube->cos_ang);
    }

    /* Clear the old cube */
    graphics_FillScreen(255);

    /* Every 200 draws, change the color */
    if (drawnTimes % 200 == 0) {
        graphics_SetColor(rand());
    }
    drawnTimes++;

    /* Draw the new cube */
    for (uint8_t i = 0; i < 4; ++i) {
        uint8_t j = i + 1 & 3;
        graphics_Line(face1[i][0], face1[i][1], face1[j][0], face1[j][1]);
        graphics_Line(face2[i][0], face2[i][1], face2[j][0], face2[j][1]);
        graphics_Line(face1[i][0], face1[i][1], face2[i][0], face2[i][1]);
    }
}

void render_loop(void) {
    static cube_t cube;

    /* Set up the intial cube positions */
    cube.sin_ang = sinf(ANG);
    cube.cos_ang = cosf(ANG);
    cube.midx1 = (face1[0][0] + face1[1][0]) / 2.0f;
    cube.midy1 = (face1[1][1] + face1[2][1]) / 2.0f;
    cube.midx2 = (face2[0][0] + face2[1][0]) / 2.0f;
    cube.midy2 = (face2[1][1] + face2[2][1]) / 2.0f;

    /* Loop until a key is pressed */
    do
    {
        /* Rotate the cube */
        rotate(&cube);

        /* Swap the buffer with the screen */
        graphics_SwapDraw();

    } while (!os_GetCSC());
}

/* lcddrvce column major mode */

void begin_column_major(void) {
    graphics_Begin();

    lcd_Init();
    lcd_SetRamAccessOrder(LCD_MADCTL_DEFAULT ^ LCD_MV);
    lcd_SetColumnAddress(0, 239);
    lcd_SetRowAddress(0, 319);
}

void end_column_major(void) {
	lcd_SetRamAccessOrder(LCD_MADCTL_DEFAULT);
    lcd_SetColumnAddress(0, 319);
    lcd_SetRowAddress(0, 239);
    lcd_Cleanup();

    graphics_End();
}

int main(void) {

    begin_column_major();

    render_loop();

    end_column_major();

    return 0;
}

