; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; void *memcpy( void *dest, const void *src, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memcpy
_memcpy:
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)	;count
	sbc	hl,hl
	sbc	hl,bc	;count==0?
	jr	z,_L0
	ld	de,(iy+3)	;dest
	ld	hl,(iy+6)	;src
	ldir
_L0:
	ld	hl,(iy+3)	;dest
	ret

	END
