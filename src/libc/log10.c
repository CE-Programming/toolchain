#include <math.h>

float _log10f_c(float x)
{
    return logf(x) / M_LN10;
}

double _log10_c(double) __attribute__((alias("_log10f_c")));
