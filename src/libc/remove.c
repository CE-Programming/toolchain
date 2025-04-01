#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) remove(const char *filename)
{
	return !ti_Delete(filename);
}
