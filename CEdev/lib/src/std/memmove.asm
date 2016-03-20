; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <string.h>
; void *memmove( void *dest, const void *src, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memmove
	
_memmove       equ 0000A8h

	END
