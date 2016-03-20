; (c) Copyright 2016 Matt Waltz
;-------------------------------------------------------------------------
; Faster memset variation
; Reasons faster:
;  1) uses ldir to memset
;  2) executes in RAM to avoid flash wait states
;-------------------------------------------------------------------------
	.def	_memset_fast
	.assume adl=1

_memset_fast:
	push	ix
	ld	ix,6
	add	ix,sp
	ld	hl,(ix)
	ld	bc,0
	or	a,a
	sbc	hl,bc
	jr	z,ret
	ld	hl,(ix)
	ld	bc,(ix+06)
	ld	a,(ix+03)
	ld	(hl),a
	dec	bc
	or	a,a
	sbc	hl,hl
	sbc	hl,bc
	jr	z,ret
	ld	hl,(ix)
	ld	de,(ix)
	inc	de
	ldir
	ld	hl,(ix)
ret:
	pop	ix
	ret
	
	end