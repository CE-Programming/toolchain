/* public domain rewrite of finite(3) */
#include <math.h>

int finite(double n) {
    return !isnan(n) && !isinf(n);
}