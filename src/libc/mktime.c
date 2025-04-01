#include <tice.h>
#include <time.h>
#include <stdint.h>

#define SECS_PER_DAY   86400u
#define SECS_PER_HOUR  3600u
#define SECS_PER_MIN   60u

time_t mktime(struct tm *tp)
{
	static const int yday[] = { -1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333 };

	return
		tp->tm_sec +
		tp->tm_min * SECS_PER_MIN +
		tp->tm_hour * SECS_PER_HOUR +
		(yday[tp->tm_mon] + tp->tm_mday) * SECS_PER_DAY +
		(tp->tm_year - 70) * 31536000 + ((tp->tm_year - 69) / 4) * SECS_PER_DAY -
		((tp->tm_year - 1) / 100) * SECS_PER_DAY + ((tp->tm_year + 299) / 400) * SECS_PER_DAY;
}

