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
	ld	iy,0
	add	iy,sp
	ld	bc,(iy+9)
	sbc	hl,hl 
	adc	hl,bc
	jr	z,ret
	ld	hl,(iy+3)
	ld	a,(iy+6)
	ld	(hl),a
	cpi
	ex	de,hl
	ld	hl,(iy+3)
	jp	po,ret
	ldir
ret:	ld	hl,(iy+3)
	ret
	
	end
