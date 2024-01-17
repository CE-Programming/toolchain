#include <tice.h>
#include <time.h>
#include <stdint.h>

time_t time(time_t *timer)
{
    uint8_t sec, min, hrs;
    uint8_t day, month;
    uint16_t year;
    struct tm tm2;
    time_t res;

    boot_GetDate(&day, &month, &year);
    boot_GetTime(&sec, &min, &hrs);

    tm2.tm_sec = sec;
    tm2.tm_min = min;
    tm2.tm_hour = hrs;
    tm2.tm_mday = day;
    tm2.tm_mon = month - 1;
    tm2.tm_year = (unsigned int)year - 1900;

    res = mktime(&tm2);

    if (timer != NULL)
    {
        *timer = res;
    }

    return res;
}
