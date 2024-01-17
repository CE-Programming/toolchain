#ifndef _TIME_H
#define _TIME_H

#include <cdefs.h>

#ifndef LOCALTIME_GMT_OFFSET
#define LOCALTIME_GMT_OFFSET 0
#endif

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 32768UL
#endif

typedef unsigned long time_t;
typedef unsigned long clock_t;

struct tm {
   int tm_sec;
   int tm_min;
   int tm_hour;
   int tm_mday;
   int tm_mon;
   int tm_year;
   int tm_wday;
   int tm_yday;
   int tm_isdst;
};

__BEGIN_DECLS

clock_t clock(void);

double difftime(time_t time1, time_t time0)
    __attribute__((__const__));

time_t mktime(struct tm *tmp);

time_t time(time_t *timer);

struct tm *localtime(const time_t *timer);

struct tm *gmtime(const time_t *timer);

char *asctime(const struct tm *tmp);

char *ctime(const time_t *timer);

size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr);

__END_DECLS

#endif /* _TIME_H */
