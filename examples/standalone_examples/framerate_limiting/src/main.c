#include <ti/screen.h>
#include <ti/getcsc.h>
#include <time.h>
#include <debug.h>

/* The framerate to limit to */
#define TARGET_FRAMERATE 20

/* The (approximate) amount of time each frame should take, in clock ticks */
#define TARGET_FRAME_TIME (CLOCKS_PER_SEC / TARGET_FRAMERATE)

/**
 * Draws a spinner to the top-left corner of the screen.
*/
static void draw_spinner(void)
{
    static int char_num = 0;
    const char characters[] = {'|', '/', '-', '\\'};

    char character = characters[char_num];

    /* Convert the character into a null-terminated string. */
    char str[2] = { character, '\0' };

    /* Draw the string to the screen. */    
    os_SetCursorPos(0, 0);
    os_PutStrFull(str);

    /* Move to the next character, looping back to the first when
       we reach the end. */
    char_num = (char_num + 1) % 4;
}

int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Wait for a key */
    while (!os_GetCSC()) {
        /* Get the time that the frame starts. */
        clock_t frame_start = clock();

        /* Do graphical stuff. */
        draw_spinner();

        /* Get how much time has elapsed since the start of the frame. */
        clock_t frame_time = clock() - frame_start;

        if (frame_time > TARGET_FRAME_TIME) {
            dbg_printf("Warning! Frame took too long (%li clock ticks). "
                       "The maximum frame time for %u FPS is %u clock ticks.\n",
                       frame_time, TARGET_FRAMERATE, TARGET_FRAME_TIME);
        }

        /* Wait for at least TARGET_FRAME_TIME to have passed since
           the start of the frame. */
        do {
            frame_time = clock() - frame_start;
        } while (frame_time < TARGET_FRAME_TIME);

        /* Note that there should not be any code below the above loop,
           since it would not be counted towards the frame time. */
    }

    return 0;
}
