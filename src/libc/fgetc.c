#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fgetc(FILE *stream)
{
	int c;

	if (stream == NULL ||
		stream == stdout ||
		stream == stderr)
	{
		c = EOF;
	}
	else if (stream == stdin)
	{
		c = getchar();
	}
	else
	{
		c = ti_GetC(stream->slot);
	}

	if (c == EOF)
	{
		stream->eof = 1;
	}

	return c;
}
