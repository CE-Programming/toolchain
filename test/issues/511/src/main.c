#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <ti/getcsc.h>
#include <ti/screen.h>

int main(void)
{
    static const uint8_t values[][4] =
    {
        { 0xcf, 0x7f, 0x39, 0xbe },  /* -0.18115161359 */
        { 0xcf, 0xff, 0x39, 0xbe },  /* -0.18163998 */
        { 0x00, 0x00, 0x00, 0x00 },  /* +0 */
        { 0x00, 0x00, 0x00, 0x80 },  /* -0 */
        { 0x00, 0x00, 0x80, 0x7f },  /* +inf */
        { 0x00, 0x00, 0x80, 0xff },  /* -inf */
        { 0x00, 0x01, 0x80, 0x7f },  /* NaN */
        { 0x00, 0x01, 0x80, 0xff },  /* NaN */
        { 0x00, 0x00, 0x10, 0x7f },  /* out-of-range */
        { 0x00, 0x00, 0x10, 0xff },  /* out-of-range */
    };

    /* expected output */
    /*
        Test  1: inf = N, NaN = N: -0.181152 (cf 7f 39 be)
        Test  2: inf = N, NaN = N: -0.181640 (cf ff 39 be)
        Test  3: inf = N, NaN = N: 0.000000 (00 00 00 00)
        Test  4: inf = N, NaN = N: -0.000000 (00 00 00 80)
        Test  5: inf = Y, NaN = N: inf (00 00 80 7f)
        Test  6: inf = Y, NaN = N: -inf (00 00 80 ff)
        Test  7: inf = N, NaN = Y: nan (00 01 80 7f)
        Test  8: inf = N, NaN = Y: -nan (00 01 80 ff)
        Test  9: inf = N, NaN = N: err (00 00 10 7f)
        Test 10: inf = N, NaN = N: -err (00 00 10 ff)
    */

    for (size_t i = 0; i < sizeof(values) / sizeof(*values); ++i)
    {
        float dx;

        memcpy(&dx, values[i], sizeof dx);

        os_ClrHome();

        printf("inf = %c, NaN = %c: %f (%02x %02x %02x %02x)\r\n",
            isinf(dx) ? 'Y' : 'N',
            isnan(dx) ? 'Y' : 'N',
            dx, values[i][0], values[i][1], values[i][2], values[i][3]);

        while (!os_GetCSC());
    }

    return 0;
}
