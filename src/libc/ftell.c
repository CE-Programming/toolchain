#include <stdio.h>
#include <fileioc.h>

long int __attribute__((weak)) ftell(FILE *stream)
{
	if (stream == NULL ||
		stream == stdin ||
		stream == stdout ||
		stream == stderr)
	{
		return -1L;
	}

	return (long int)ti_Tell(stream->slot);
}
