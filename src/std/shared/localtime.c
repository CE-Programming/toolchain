#include <tice.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#define SECS_PER_MIN 60UL

struct tm *localtime(const time_t *timer)
{
    time_t timer2 = *timer;
    timer2 -= LOCALTIME_GMT_OFFSET * SECS_PER_MIN;

    return gmtime(&timer2);
}
