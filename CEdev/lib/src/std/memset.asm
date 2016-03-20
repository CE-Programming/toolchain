; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; void *memset( void *dest, int c, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memset
	
_memset        equ 0000ACh

	END

