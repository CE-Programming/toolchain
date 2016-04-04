; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; void *memchr( const void *buf, int c, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memchr
_memchr:
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)	;count
	sbc	hl,hl
	sbc	hl,bc	;count==0?
	ret	z
	ld	hl,(iy+3)	;buf
	ld	a,(iy+6)	;c
	cpir
	dec	hl
	ret	z
	or	a,a
	sbc	hl,hl
	ret

	end
