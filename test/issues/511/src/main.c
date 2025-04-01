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
		{ 0xcf, 0x7f, 0x39, 0xbe },  /* -0.181151 */
		{ 0xcf, 0xff, 0x39, 0xbe },  /* -0.181639 */
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
		inf = N, NaN = N: -0.181151 (cf 7f 39 be)
		inf = N, NaN = N: -0.181639 (cf ff 39 be)
		inf = N, NaN = N: 0.000000 (00 00 00 00)
		inf = N, NaN = N: -0.000000 (00 00 00 80)
		inf = Y, NaN = N: inf (00 00 80 7f)
		inf = Y, NaN = N: -inf (00 00 80 ff)
		inf = N, NaN = Y: nan (00 01 80 7f)
		inf = N, NaN = Y: -nan (00 01 80 ff)
		inf = N, NaN = N: oor (00 00 10 7f)
		inf = N, NaN = N: -oor (00 00 10 ff)
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
