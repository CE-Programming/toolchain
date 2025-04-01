#include <fileioc.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

extern FILE _file_streams[FOPEN_MAX];

FILE* __attribute__((weak)) fopen(const char *__restrict filename, const char *__restrict mode)
{
	ti_var_t slot;
	uint8_t index;

	slot = ti_Open(filename, mode);
	if (slot == 0)
	{
		return NULL;
	}

	index = slot - 1;
	_file_streams[index].slot = slot;
	_file_streams[index].eof = 0;
	_file_streams[index].err = 0;

	return &_file_streams[index];
}
