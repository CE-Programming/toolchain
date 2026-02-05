
// (a + ib) + (c + id)
_Complex float __addsc3(float a, float b, float c, float d) {
    return (a + c) + (b + d) * 1.0iF;
}

// (a + ib) - (c + id)
_Complex float __subsc3(float a, float b, float c, float d) {
    return (a - c) + (b - d) * 1.0iF;
}

// (a + ib) * (c + id)
_Complex float __mulsc3(float a, float b, float c, float d) {
    return (a * c - b * d) + (a * d + b * c) * 1.0iF;
}

// (a + ib) / (c + id)
// Uses stable algorithm to avoid overflow/underflow issues
_Complex float __divsc3(float a, float b, float c, float d) {
    float r, den;
    float real, imag;

    if (__builtin_fabsf(c) >= __builtin_fabsf(d)) {
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

    return real + imag * 1.0iF;
}
