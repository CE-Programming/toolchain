#include <ti/screen.h>
#include <ti/getcsc.h>

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool check_division(int numerator, int denominator)
{
    if (!denominator || (numerator == INT_MIN && denominator == -1)) {
        return true; /* Division is undefined for these inputs. */
    }

    uint32_t dividend = numerator < 0 ? UINT32_C(0) - (uint32_t)numerator
                                     : (uint32_t)numerator;
    uint32_t divisor = denominator < 0 ? UINT32_C(0) - (uint32_t)denominator
                                      : (uint32_t)denominator;
    uint32_t quotient = 0, remainder = 0;

    /* Independent oracle: do not use /, %, or another CRT divider. */
    for (int bit = sizeof(unsigned) * CHAR_BIT - 1; bit >= 0; --bit) {
        remainder = (remainder << 1) | ((dividend >> bit) & UINT32_C(1));
        if (remainder >= divisor) {
            remainder -= divisor;
            quotient |= UINT32_C(1) << bit;
        }
    }

    /* Construct INT_MIN without converting its unsigned magnitude to int. */
    int expected_quotient = ((numerator < 0) != (denominator < 0)) && quotient
                         ? -(int)(quotient - 1) - 1 : (int)quotient;
    int expected_remainder = numerator < 0 ? -(int)remainder : (int)remainder;
    /* -ffreestanding keeps this a call to libc div(). */
    div_t actual = div(numerator, denominator);

    if (actual.quot != expected_quotient || actual.rem != expected_remainder) {
        printf("div(%d,%d)\ngot %d,%d\nexpected %d,%d\n",
               numerator, denominator, actual.quot, actual.rem,
               expected_quotient, expected_remainder);
        return false;
    }
    return true;
}

static bool run_tests(void)
{
    /* The modular-inverse failure that exposed the OS CRT sign bug. */
    if (!check_division(23, 10)) {
        return false;
    }

    for (int numerator = -64; numerator <= 64; ++numerator) {
        for (int denominator = -23; denominator <= 23; ++denominator) {
            if (!check_division(numerator, denominator)) {
                return false;
            }
        }
    }

    static const int edges[] = {
        INT_MIN, -INT_MAX, -65537, -256, -23, -7, -1,
        0, 1, 2, 7, 23, 255, 256, 65537, INT_MAX
    };
    for (unsigned numerator = 0; numerator < sizeof(edges)/sizeof(edges[0]); ++numerator) {
        for (unsigned denominator = 0; denominator < sizeof(edges)/sizeof(edges[0]); ++denominator) {
            if (!check_division(edges[numerator], edges[denominator])) {
                return false;
            }
        }
    }
    return true;
}

int main(void)
{
    os_ClrHome();
    if (run_tests()) {
        fputs("All tests passed", stdout);
    }
    while (!os_GetCSC());
    return 0;
}
