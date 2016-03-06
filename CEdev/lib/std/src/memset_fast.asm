; (c) Copyright 2016 Matt Waltz
;-------------------------------------------------------------------------
; Fast memset routine
;-------------------------------------------------------------------------
	.def	_memset_fast
	.assume adl=1

_memset_fast:
	push	ix
	ld	ix,6
	add	ix,sp
	ld	de,(ix)
	ld	hl,(ix)
	ld	a,(ix+03)
	ld	bc,(ix+06)
	inc	de
	ld	(hl),a
	ldir
	ld	hl,(ix)
	pop	ix
	ret