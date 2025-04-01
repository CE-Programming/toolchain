#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fputs(const char *__restrict str, FILE *__restrict stream)
{
	unsigned int i = 0;
	char c;

	while ((c = str[i]))
	{
		if (fputc(c, stream) == EOF)
		{
			return EOF;
		}
		i++;
	}

	return 1;
}
