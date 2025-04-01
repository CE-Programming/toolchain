#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fputc(int c, FILE *stream)
{
	int ret;

	if (stream == NULL || stream == stdin)
	{
		ret = EOF;
	}
	else if (stream == stdout || stream == stderr)
	{
		ret = putchar(c);
	}
	else
	{
		ret = ti_PutC((char)c, stream->slot);
	}

	if (ret == EOF)
	{
		stream->eof = 1;
	}

	if (ret != c)
	{
		stream->err = 1;
	}

	return ret;
}
