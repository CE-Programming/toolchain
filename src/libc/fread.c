#include <stdio.h>
#include <fileioc.h>

size_t __attribute__((weak)) fread(void *ptr, size_t size, size_t count, FILE *__restrict stream)
{
	size_t ncount;

	if (stream == NULL ||
		stream == stdout ||
		stream == stderr)
	{
		return 0;
	}

	if (stream == stdin)
	{
		int c;
		char *p = ptr;
		size_t len = size * count;

		for (; len > 0; len--)
		{
			if ((c = fgetc(stream)) == EOF)
			{
				break;
			}
			*p++ = c;
		}

		return count;
	}

	ncount = ti_Read(ptr, size, count, stream->slot);
	if (ncount != count)
	{
		stream->err = 1;
	}

	return ncount;
}
