#include <graphx.h>

void begin(void);
void end(void);
bool step(void);
void draw(void);

int main(void)
{
    bool partial_redraw = false;

    /* No rendering allowed! */
    begin();

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Draw to the buffer to avoid rendering artifacts */
    gfx_SetDrawBuffer();

    /* No rendering allowed in step! */
    while (step())
    {
        /* Only want to redraw part of the previous frame? */
        if (partial_redraw)
        {
            /* Copy previous frame as a base for this frame */
            gfx_BlitScreen();
        }

        /* As little non-rendering logic as possible */
        draw();

        /* Queue the buffered frame to be displayed */
        gfx_SwapDraw();
    }

    /* End graphics drawing */
    gfx_End();
    end();

    return 0;
}

/* Implement me! */
void begin(void)
{

}

/* Implement me! */
void end(void)
{

}

/* Implement me! */
bool step(void)
{
    return false;
}

/* Implement me! */
void draw(void)
{

}
