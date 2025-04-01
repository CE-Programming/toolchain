#include <ti/screen.h>
#include <ti/getkey.h>
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
	volatile uint64_t x = 3750000;

	os_ClrHome();

	x *= 2.5;

	printf("value: %llu\n", x);

	os_GetKey();

	return 0;
}
