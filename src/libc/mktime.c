#include <tice.h>
#include <time.h>
#include <stdint.h>

#define SECS_PER_DAY   86400UL
#define SECS_PER_HOUR  3600UL
#define SECS_PER_MIN   60UL
#define DAYS_PER_YEAR  365UL

extern bool __isleap(int year);

time_t mktime(struct tm *tp)
{
    static const unsigned int dpmt[] =
    {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    unsigned int i;
    time_t days;

    if (tp->tm_year < (1970 - 1900))
    {
        return -1L;
    }

    days = (tp->tm_year - (1970 - 1900)) * DAYS_PER_YEAR;

    for (i = 1970; i < (unsigned int)tp->tm_year + 1900; ++i)
    {
        if (__isleap(i))
        {
            days++;
        }
    }

    days += dpmt[tp->tm_mon];
    if (__isleap(tp->tm_year))
    {
        days++;
    }

    days += tp->tm_mday - 1;

    days *= SECS_PER_DAY;

    days += (tp->tm_hour * SECS_PER_HOUR) + (tp->tm_min * SECS_PER_MIN) + tp->tm_sec;

    return days;
}
