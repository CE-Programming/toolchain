#include <stdio.h>
#include <fileioc.h>

size_t __attribute__((weak)) fwrite(const void *__restrict ptr, size_t size, size_t count, FILE *__restrict stream)
{
	size_t ncount;

	if (stream == NULL ||
		stream == stdin)
	{
		return 0;
	}

	if (stream == stdout ||
		stream == stderr)
	{
		char *p = (char *)ptr;
		size_t len = size * count;
		size_t num = 0;

		for (; len > 0; len--)
		{
			if (putchar(*p++) == EOF)
			{
				break;
			}
			num++;
		}

		return num / size;
	}

	ncount = ti_Write(ptr, size, count, stream->slot);
	if (ncount != count)
	{
		stream->err = 1;
	}

	return ncount;
}
