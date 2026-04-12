#include <stdint.h>
#include <graphx.h>
#include <ti/getcsc.h>

static void draw_base_pattern(void)
{
    uint8_t stripe;

    gfx_FillScreen(239);

    gfx_SetColor(26);
    gfx_FillRectangle_NoClip(0, 0, GFX_LCD_WIDTH, 14);
    gfx_SetColor(27);
    gfx_FillRectangle_NoClip(0, GFX_LCD_HEIGHT - 12, GFX_LCD_WIDTH, 12);

    for (stripe = 0; stripe < 6; stripe++)
    {
        static const uint8_t colors[6] = { 224, 9, 27, 56, 186, 250 };
        uint24_t x = 24 + stripe * 40;

        gfx_SetColor(colors[stripe]);
        gfx_FillRectangle_NoClip(x, 24, 40, 120);

        gfx_SetColor(0);
        gfx_VertLine_NoClip(x, 24, 120);
        gfx_VertLine_NoClip(x + 39, 24, 120);

        gfx_SetColor(255);
        gfx_FillRectangle_NoClip(x + 6, 34 + stripe * 12, 28, 6);
        gfx_FillRectangle_NoClip(x + 6, 108 - stripe * 10, 28, 6);
    }

    gfx_SetColor(0);
    gfx_Rectangle_NoClip(23, 23, 241, 121);

    gfx_SetTextFGColor(255);
    gfx_SetTextBGColor(26);
    gfx_PrintStringXY("gfx_CopyRectangle overlap demo", 6, 3);

    gfx_SetTextFGColor(255);
    gfx_SetTextBGColor(27);
    gfx_PrintStringXY("Black border = SRC   White border = DST", 6, GFX_LCD_HEIGHT - 10);
}

static void draw_overlay(const char *title,
                         uint24_t src_x,
                         uint8_t src_y,
                         uint24_t dst_x,
                         uint8_t dst_y,
                         uint24_t width,
                         uint8_t height)
{
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(src_x - 1, src_y - 1, width + 2, height + 2);

    gfx_SetColor(255);
    gfx_Rectangle_NoClip(dst_x - 1, dst_y - 1, width + 2, height + 2);

    gfx_SetColor(255);
    gfx_FillRectangle_NoClip(src_x + 2, src_y + 2, 24, 10);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(src_x + 2, src_y + 2, 24, 10);
    gfx_SetTextFGColor(0);
    gfx_SetTextBGColor(255);
    gfx_PrintStringXY("SRC", src_x + 4, src_y + 3);

    gfx_SetColor(255);
    gfx_FillRectangle_NoClip(dst_x + 2, dst_y + 2, 24, 10);
    gfx_SetColor(0);
    gfx_Rectangle_NoClip(dst_x + 2, dst_y + 2, 24, 10);
    gfx_SetTextFGColor(0);
    gfx_SetTextBGColor(255);
    gfx_PrintStringXY("DST", dst_x + 4, dst_y + 3);

    gfx_SetColor(52);
    gfx_FillRectangle_NoClip(188, 2, 130, 10);
    gfx_SetTextFGColor(255);
    gfx_SetTextBGColor(52);
    gfx_PrintStringXY(title, 192, 3);
}

static void show_stage(void)
{
    gfx_BlitBuffer();
    while (!os_GetCSC())
    {
    }
}

int main(void)
{
    gfx_Begin();
    gfx_SetDrawBuffer();

    draw_base_pattern();
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 24, 18, 72, 18, 180, 64);
    draw_overlay("Move right", 24, 18, 72, 18, 180, 64);
    show_stage();

    draw_base_pattern();
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 72, 18, 24, 18, 180, 64);
    draw_overlay("Move left", 72, 18, 24, 18, 180, 64);
    show_stage();

    draw_base_pattern();
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 30, 24, 30, 60, 128, 96);
    draw_overlay("Move down", 30, 24, 30, 60, 128, 96);
    show_stage();

    draw_base_pattern();
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 30, 60, 30, 24, 128, 96);
    draw_overlay("Move up", 30, 60, 30, 24, 128, 96);
    show_stage();

    gfx_End();

    return 0;
}
