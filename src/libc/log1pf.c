#include <math.h>

float log1pf(float x) {
    if (fabsf(x) <= 0.125) {
        // pade(series(ln(1+x),x=0,6,polynom),x,5,3)
        // (-57*x**2-90*x)/(x**3-21*x**2-102*x-90)
        // relative error less than 1e-7
        return x*(57*x+90)/(((21-x)*x+102)*x+90);
    }
    // relative error about 2^-21 if abs(x) is just above 0.125
    return logf(1 + x);
}

double log1p(double) __attribute__((alias("log1pf")));
