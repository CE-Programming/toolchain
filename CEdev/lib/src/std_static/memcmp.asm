; Copyright (C) 1999-2008 Zilog, Inc, All Rights Reserved
;-------------------------------------------------------------------------
; <memory.h> <string.h>
; int memcmp( const void *buf1, const void *buf2, size_t count );
;-------------------------------------------------------------------------
	.assume ADL=1
	XDEF _memcmp
_memcmp:
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)	;count
	sbc	hl,hl
	sbc	hl,bc	;count==0?
	ret	z
	ld	de,(iy+3)	;buf1
	ld	hl,(iy+6)	;buf2
_Loop:
	ld	a,(de)
	cpi
	jr	nz,_L0
	inc	de
	jp	pe,_Loop
	or	a,a
	sbc	hl,hl
	ret
_L0:
	dec	hl
	cp	a,(hl)
	sbc	hl,hl
	ret	c
	inc	hl
	ret

	END
