#include <time.h>
#include <stdio.h>

double difftime(time_t end, time_t beginning)
{
	/* assuming typedef unsigned long time_t */
    return (double)((signed long)(end - beginning));
}
