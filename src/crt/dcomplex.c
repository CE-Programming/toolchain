
// (a + ib) + (c + id)
_Complex long double __adddc3(long double a, long double b, long double c, long double d) {
    return (a + c) + (b + d) * 1.0iL;
}

// (a + ib) - (c + id)
_Complex long double __subdc3(long double a, long double b, long double c, long double d) {
    return (a - c) + (b - d) * 1.0iL;
}

// (a + ib) * (c + id)
_Complex long double __muldc3(long double a, long double b, long double c, long double d) {
    return (a * c - b * d) + (a * d + b * c) * 1.0iL;
}

// (a + ib) / (c + id)
// Uses stable algorithm to avoid overflow/underflow issues
_Complex long double __divdc3(long double a, long double b, long double c, long double d) {
    long double r, den;
    long double real, imag;

    if (__builtin_fabsl(c) >= __builtin_fabsl(d)) {
        r   = d / c;
        den = c + d * r;
        real = (a + b * r) / den;
        imag = (b - a * r) / den;
    } else {
        r   = c / d;
        den = d + c * r;
        real = (a * r + b) / den;
        imag = (b * r - a) / den;
    }

    return real + imag * 1.0iL;
}
