#include <stdbool.h>
#include <stdint.h>

extern bool __isleap(int year)
{
    if( year % 100 == 0 )
    {
        return year % 400 == 0;
    }

    return year % 4 == 0;
}
