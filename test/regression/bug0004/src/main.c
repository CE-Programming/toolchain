#include <ti/screen.h>
#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
    bool clip = false;

    gfx_Begin();

    gfx_FillScreen(0x07);
    gfx_SetTransparentColor(0x18);
    gfx_SetTextTransparentColor(0xE0);
    gfx_SetTextBGColor(0x18);
    gfx_SetTextFGColor(0xE0);

    for (const char *c = "Hello, world!"; *c != '\0'; ++c, clip = !clip)
    {
        gfx_SetTextConfig(clip ? gfx_text_clip : gfx_text_noclip);
        gfx_PrintChar(*c);
    }

    while (!os_GetCSC());

    gfx_End();

    return 0;
}
