; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; void *memchr( const void *buf, int c, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memchr
	
_memchr        equ 00009Ch

	end
