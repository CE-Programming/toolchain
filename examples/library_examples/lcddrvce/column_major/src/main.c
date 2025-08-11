#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <ti/getcsc.h>
#include <graphx.h>
#include <lcddrvce.h>

#define ORG (-50)
#define DEG (6.0)
#define ANG (DEG * M_PI / 180.0)

typedef struct {
    float sin_ang;
    float cos_ang;
    float midx1;
    float midy1;
    float midx2;
    float midy2;
} cube_t;

static float face1[4][2] = {
    { 140,  45 },
    { 240,  45 },
    { 240, 145 },
    { 140, 145 },
};

static float face2[4][2] = {
    { 140 + ORG,  45 - ORG },
    { 240 + ORG,  45 - ORG },
    { 240 + ORG, 145 - ORG },
    { 140 + ORG, 145 - ORG },
};

uint8_t line_color;

void draw_line(uint24_t x0, uint8_t y0, uint24_t x1, uint8_t y1);

void rotate(cube_t *cube);

int main(void) {
    static cube_t cube;

    /* Set up the intial cube positions */
    cube.sin_ang = sin(ANG);
    cube.cos_ang = cos(ANG);
    cube.midx1 = (face1[0][0] + face1[1][0]) / 2;
    cube.midy1 = (face1[1][1] + face1[2][1]) / 2;
    cube.midx2 = (face2[0][0] + face2[1][0]) / 2;
    cube.midy2 = (face2[1][1] + face2[2][1]) / 2;

    /* Start the graphics routines */
    gfx_Begin();
    gfx_SetDrawBuffer();

    /* Setup Column-Major mode (240x320) */
    lcd_Init();
    lcd_SetRamAccessOrder(LCD_MADCTL_DEFAULT ^ LCD_MV);
    lcd_SetColumnAddress(0, GFX_LCD_HEIGHT - 1);
    lcd_SetRowAddress(0, GFX_LCD_WIDTH - 1);

    /* Loop until a key is pressed */
    do {
        /* Rotate the cube */
        rotate(&cube);

        /* Swap the buffer with the screen */
        gfx_SwapDraw();

    } while (!os_GetCSC());

    /* Restore Row-Major mode (320x240) */
    lcd_SetRamAccessOrder(LCD_MADCTL_DEFAULT);
    lcd_SetColumnAddress(0, GFX_LCD_WIDTH - 1);
    lcd_SetRowAddress(0, GFX_LCD_HEIGHT - 1);
    lcd_Cleanup();

    /* End graphics drawing */
    gfx_End();

    return 0;
}

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
    gfx_FillScreen(255);

    /* Every 200 draws, change the color */
    if (drawnTimes % 200 == 0) {
        line_color = rand();
    }
    drawnTimes++;

    /* Draw the new cube */
    for (uint8_t i = 0; i < 4; ++i) {
        uint8_t j = (i + 1) & 3;
        draw_line(face1[i][0], face1[i][1], face1[j][0], face1[j][1]);
        draw_line(face2[i][0], face2[i][1], face2[j][0], face2[j][1]);
        draw_line(face1[i][0], face1[i][1], face2[i][0], face2[i][1]);
    }
}

/* Bresenham line drawing code */

static void draw_line0(int x0, int y0, int x1, int y1) {
    int dX = x1 - x0;
    int dY = y1 - y0;
    int y_incr = 1;
    if (dY < 0) {
        y_incr = -1;
        dY = -dY;
    }
    int dD = 2 * dY - dX;
    const int dD_jump = 2 * (dY - dX);
    dY *= 2;

    uint8_t* buffer = (uint8_t*)gfx_vbuffer + (x0 * GFX_LCD_HEIGHT) + y0;
    const uint8_t color = line_color;

    for (uint24_t x = (uint24_t)dX; x > 0; x--) {
        *buffer = color;
        /* Moves right one pixel */
        buffer += GFX_LCD_HEIGHT;
        if (dD > 0) {
            buffer += y_incr;
            dD += dD_jump;
        } else {
            dD += dY;
        }
    }
}

static void draw_line1(int x0, int y0, int x1, int y1) {
    int dX = x1 - x0;
    int dY = y1 - y0;
    int x_incr = GFX_LCD_HEIGHT;
    if (dX < 0) {
        x_incr = -GFX_LCD_HEIGHT;
        dX = -dX;
    }
    int dD = (2 * dX) - dY;
    const int dD_jump = 2 * (dX - dY);
    dX *= 2;

    uint8_t* buffer = (uint8_t*)gfx_vbuffer + (x0 * GFX_LCD_HEIGHT) + y0;
    const uint8_t color = line_color;

    for (uint8_t y = (uint8_t)dY; y > 0; y--) {
        *buffer = color;
        /* Moves down one pixel */
        ++buffer;
        if (dD > 0) {
            buffer += x_incr;
            dD += dD_jump;
        } else {
            dD += dX;
        }
    }
}

void draw_line(uint24_t x0, uint8_t y0, uint24_t x1, uint8_t y1) {
    if (abs((int)y1 - (int)y0) < abs((int)x1 - (int)x0)) {
        if (x0 > x1) {
            draw_line0(x1, y1, x0, y0);
        } else {
            draw_line0(x0, y0, x1, y1);
        }
    } else {
        if (y0 > y1) {
            draw_line1(x1, y1, x0, y0);
        } else {
            draw_line1(x0, y0, x1, y1);
        }
    }
}
