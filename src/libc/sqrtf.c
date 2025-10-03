#include <errno.h>
#include <math.h>
#include <stdint.h>

/*
; only works for normalized values
; CC: 9F + 12R + 9W + 1 | 8 bytes
__f32_fast_div4:
	pop	bc, hl, de
	dec	e	; subtracts 2 from the exponent
	push	de, hl, bc
	ret
*/
float _f32_fast_div4(float x) __attribute__((__const__, __leaf__, __nothrow__));

/**
 * @remarks Minimum ulp of -1
 */
float _sqrtf_c(float x)
{
    float f, y;
    int n;

    if (x == 0.0f) {
        return x;
    }
    if (x == 1.0f) {
        return 1.0f;
    }
    if (x < 0.0f) {
        errno = EDOM;
        /* return a "NaN" value */
        return 0.0f;
    }
    f = frexpf(x, &n);
    y = 0.41731f + 0.59016f * f; /* Educated guess */
    /* For a 24 bit mantisa (float), two iterations are sufficient */
    y += f / y;
    y = _f32_fast_div4(y) + f / y; /* Faster version of 0.25f * y + f/y */

    if (n & 1) {
        y *= (float)M_SQRT1_2;
        ++n;
    }
    /* n will be [-148, 128] prior to division */
    return ldexpf(y, n/2);
}

double _sqrt_c(double) __attribute__((alias("_sqrtf_c")));
