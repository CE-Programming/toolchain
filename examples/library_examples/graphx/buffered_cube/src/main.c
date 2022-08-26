#include <math.h>
#include <graphx.h>
#include <ti/getcsc.h>

#define ORG (-50)
#define DEG (6.0)
#define ANG (DEG * M_PI / 180.0)

typedef struct
{
    float sin_ang;
    float cos_ang;
    float midx1;
    float midy1;
    float midx2;
    float midy2;
} cube_t;

static float face1[4][2] =
{
    { 140,  45 },
    { 240,  45 },
    { 240, 145 },
    { 140, 145 },
};

static float face2[4][2] =
{
    { 140 + ORG,  45 - ORG },
    { 240 + ORG,  45 - ORG },
    { 240 + ORG, 145 - ORG },
    { 140 + ORG, 145 - ORG },
};

void rotate(cube_t *cube);

int main(void)
{
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

    /* Loop until a key is pressed */
    do
    {
        /* Rotate the cube */
        rotate(&cube);

        /* Swap the buffer with the screen */
        gfx_SwapDraw();

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}

/* Cube rotation */
void rotate(cube_t *cube)
{
    static uint8_t drawnTimes = 0;
    uint8_t i;

    /* Compute the new vertex coordinates */
    for (i = 0; i < 4; ++i)
    {
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
    if (drawnTimes % 200 == 0)
    {
        gfx_SetColor(rand());
    }
    drawnTimes++;

    /* Draw the new cube */
    for (i = 0; i < 4; ++i)
    {
        uint8_t j = i + 1 & 3;
        gfx_Line(face1[i][0], face1[i][1], face1[j][0], face1[j][1]);
        gfx_Line(face2[i][0], face2[i][1], face2[j][0], face2[j][1]);
        gfx_Line(face1[i][0], face1[i][1], face2[i][0], face2[i][1]);
    }
}
