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
	ld	hl,(iy+3)
	ld	bc,0
	or	a,a
	sbc	hl,bc
	jr	z,ret
	ld	bc,(iy+9)
	ld	a,(iy+6)
	ld	(hl),a
	push	hl
	cpi
	ex	de,hl
	pop	hl
	jp	po,ret
	ldir
ret:	ld	hl,(iy+3)
	ret
	
	end
