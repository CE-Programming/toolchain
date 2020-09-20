#include <stdint.h>
#include <tice.h>
#include <tireal.hpp>

#define ITER_MAX 15000

using namespace ti::literals;

static char buf[24] = "PI is about ";
#define buf_offset 12

int main(void)
{
    int count = 0; /* points in the unit circle's first quadrant */

    /* Clear the screen */
    os_ClrHomeFull();

    /* Set the random seed based off the real time clock */
    srand(rtc_Time());

    os_SetCursorPos(0, 0);

    for (int i = 0; i < ITER_MAX; i++)
    {
        const ti::real x = ti::real(rand()) / RAND_MAX;
        const ti::real y = ti::real(rand()) / RAND_MAX;
        const ti::real z = x*x + y*y;
        if (z <= 1)
        {
            count++;
        }
        if (i % 150 == 0) // Just to print some things along the way...
        {
            (ti::real(count) / ITER_MAX * 4).toCString(buf+buf_offset);
            os_PutStrFull(buf);
            os_NewLine();
        }
        if (os_GetCSC())
        {
            break;
        }
    }

    (ti::real(count) / ITER_MAX * 4).toCString(buf+buf_offset);
    os_PutStrFull(buf);
    os_NewLine();

    os_NewLine();
    os_PutStrFull("Press any key to quit");
    os_NewLine();

    while (!os_GetCSC());
    return 0;
}
