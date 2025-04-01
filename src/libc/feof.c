#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) feof(FILE *stream)
{
	return stream->eof;
}
