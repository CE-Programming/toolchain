	.def _memcmp
	.assume adl=1

; int memcmp(const void *buf1, const void *buf2, size_t count);
	
_memcmp		equ 0000A0h
