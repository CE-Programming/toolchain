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
	ld	iy,-1
	add	iy,sp
	ld	bc,(iy+10)
	sbc	hl,hl
	add	hl,bc
	ld	hl,(iy+4)
	ret	nc
	ex	de,hl
	lea	hl,iy+7
	push	de
	ldi
	pop	hl
	ret	po
	push	hl
	ldir
	pop	hl
	ret

	end
