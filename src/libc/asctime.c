#include <time.h>
#include <stdio.h>

char *asctime(const struct tm *timeptr)
{
    static const char wday_name[][4] =
    {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const char mon_name[][4] =
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    static char result[26];

    if (!timeptr ||
        timeptr->tm_wday < 0 || timeptr->tm_wday > 6  ||
        timeptr->tm_mon < 0  || timeptr->tm_mon > 11  ||
        timeptr->tm_mday < 1 || timeptr->tm_mday > 31 ||
        timeptr->tm_hour < 0 || timeptr->tm_hour > 23 ||
        timeptr->tm_min < 0  || timeptr->tm_min > 59  ||
        timeptr->tm_sec < 0  || timeptr->tm_sec > 60  ||
        timeptr->tm_year < -1900 || timeptr->tm_year > 8099)
    {
        return NULL;
    }

    sprintf(result, "%.3s %.3s %2d %.2d:%.2d:%.2d %d\n",
        wday_name[timeptr->tm_wday],
        mon_name[timeptr->tm_mon],
        timeptr->tm_mday,
        timeptr->tm_hour,
        timeptr->tm_min,
        timeptr->tm_sec,
        1900 + timeptr->tm_year);

    return result;
}
