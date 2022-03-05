#include <math.h>

float exp2f(float a)
{
    return expf(a * M_LOG2E);
}
