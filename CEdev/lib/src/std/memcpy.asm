; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; void *memcpy( void *dest, const void *src, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memcpy
	
_memcpy        equ 0000A4h

	END
