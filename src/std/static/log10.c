#include <math.h>

double log10(double x) {
    return log10f(x);
}

float log10f(float x) {
    return logf(x) / M_LN10;
}
