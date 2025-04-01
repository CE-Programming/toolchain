#include <ti/screen.h>
#include <ti/getkey.h>
#include <inttypes.h>
#include <stdio.h>

__attribute__((noinline)) uint64_t custom_bswap64(uint64_t x)
{
	return __builtin_bswap64(x);
}

int main(void)
{
	const uint64_t x = 0x0123456789ABCDEFull;

	os_ClrHome();

	printf("compile time:\n	0x%016" PRIX64 "\nrun time:\n	0x%016" PRIX64 "\n",
		__builtin_bswap64(x),
		custom_bswap64(x));

	os_GetKey();

	return 0;
}
