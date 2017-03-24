	.def _memset
	.assume adl=1

; void *memset(void *dest, int c, size_t count);

_memset		equ 0000ACh
