; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; void *memset( void *dest, int c, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memset
_memset:
	ld	ix,0
	add	ix,sp
	ld	de,(ix+3)	;dest
	ld	hl,(ix+9)	;count
	ld	a,(ix+6)	;c
	ld	bc,0
	jr	_L0
_Loop:
	ld	(de),a
	inc	de
	dec	hl
_L0:
	sbc	hl,bc
	jr	nz,_Loop
	ld	hl,(ix+3)	;dest
	ret

	END

