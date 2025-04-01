#include <tice.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#define SECS_PER_DAY   86400UL
#define SECS_PER_HOUR  3600UL
#define SECS_PER_MIN   60UL
#define SECS_PER_YEAR  (365UL * SECS_PER_DAY)
#define SECS_PER_LEAP  (SECS_PER_YEAR + SECS_PER_DAY)

static bool istmleap(unsigned int year)
{
	year += 1900;

	if (year % 100 == 0)
	{
		return year % 400 == 0;
	}

	return year % 4 == 0;
}

struct tm *gmtime(const time_t *tp)
{
	static uint8_t dpm[] =
	{
		31,28,31,30,31,30,31,31,30,31,30,31
	};
	static struct tm tm2;
	time_t secs_this_year;
	time_t t = *tp;

	tm2.tm_sec = 0;
	tm2.tm_min = 0;
	tm2.tm_hour = 0;
	tm2.tm_mday = 1;
	tm2.tm_mon = 0;
	tm2.tm_year = 70;
	tm2.tm_wday = (t / SECS_PER_DAY + 4) % 7;
	tm2.tm_isdst = -1;

	while (t >= (secs_this_year = istmleap(tm2.tm_year) ? SECS_PER_LEAP : SECS_PER_YEAR))
	{
		t -= secs_this_year;
		tm2.tm_year++;
	}

	while (t < 0)
	{
		t += istmleap(--tm2.tm_year) ? SECS_PER_LEAP : SECS_PER_YEAR;
	}

	tm2.tm_yday = t / SECS_PER_DAY;

	dpm[1] = 28;
	if (istmleap(tm2.tm_year))
	{
		dpm[1] = 29;
	}

	while (t >= dpm[tm2.tm_mon] * SECS_PER_DAY)
	{
		t -= dpm[tm2.tm_mon++] * SECS_PER_DAY;
	}

	while (t >= SECS_PER_DAY)
	{
		t -= SECS_PER_DAY;
		tm2.tm_mday++;
	}

	while (t >= SECS_PER_HOUR)
	{
		t -= SECS_PER_HOUR;
		tm2.tm_hour++;
	}

	while (t >= SECS_PER_MIN)
	{
		t -= SECS_PER_MIN;
		tm2.tm_min++;
	}

	tm2.tm_sec = t;

	return &tm2;
}
