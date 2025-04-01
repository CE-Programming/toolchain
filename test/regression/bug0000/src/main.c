#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdio.h>

struct s
{
	uint64_t w0;
	uint64_t b0;
	uint64_t w1;
	uint64_t b1;
	uint64_t w2;
	uint64_t b2;
	uint64_t w3;
	uint64_t b3;
	uint64_t w4;
	uint64_t b4;
	uint64_t w5;
	uint64_t b5;
};

uint8_t popcount64(uint64_t b)
{
	uint64_t b1 = (b & 0x2222222222222222) + ((b+b) & 0x2222222222222222);
	uint64_t b2 = (b >> 1 & 0x2222222222222222) + (b >> 2 & 0x2222222222222222);
	b1 = b1 + (b1 >> 4) & 0x0f0f0f0f0f0f0f0f;
	b2 = b2 + (b2 >> 4) & 0x0f0f0f0f0f0f0f0f;
	return (b1 + b2) * 0x0101010101010101 >> 57;
}

uint64_t ors(const struct s *s)
{
	return (s->b0 | s->b1 | s->b2 | s->b3 | s->b4 | s->b5) |
	   (s->w0 | s->w1 | s->w2 | s->w3 | s->w4 | s->w5);
}

int main(void)
{
	struct s s =
	{
		0xFF00 , 0x00FF000000000000,
		0x0081 , 0x8100000000000000,
		0x0042 , 0x4200000000000000,
		0x0024 , 0x2400000000000000,
		0x0010 , 0x1000000000000000,
		0x0008 , 0x0800000000000000,
	};

	os_ClrHome();

	printf("m: %llx\nf: %llx\n",
	__builtin_bswap64(((s.b0 | s.b1 | s.b2 | s.b3 | s.b4 | s.b5) |
						   (s.w0 | s.w1 | s.w2 | s.w3 | s.w4 | s.w5))),
	__builtin_bswap64(ors(&s)));

	printf("m: %u\nf: %u\n",
	popcount64(__builtin_bswap64(((s.b0 | s.b1 | s.b2 | s.b3 | s.b4 | s.b5) |
						   (s.w0 | s.w1 | s.w2 | s.w3 | s.w4 | s.w5)))),
	popcount64(__builtin_bswap64(ors(&s))));

	os_GetKey();

	return 0;
}
