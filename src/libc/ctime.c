#include <time.h>
#include <stdint.h>
#include <stdbool.h>

char *ctime(const time_t *timer)
{
	return asctime(localtime(timer));
}
