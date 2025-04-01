#include <ti/getcsc.h>
#include <graphx.h>

int main(void)
{
	gfx_Begin();

	gfx_SetColor(7); // green
	gfx_Line(-100, 20, 30, 40);

	gfx_SetColor(224); // red
	gfx_Line(30, 40, -100, 20); // same numbers as above, just flipped order

	while (!os_GetCSC());

	gfx_End();

	return 0;
}
