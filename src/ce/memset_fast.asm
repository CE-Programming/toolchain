	.def	_memset_fast
	.assume adl=1

_memset_fast:
	pop	iy
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	push	iy
	cpi
	add	hl,bc
	ret	c
	dec	hl
	ld	(hl),e
	ret	po
	push	hl
	pop	de
	dec	de
	lddr
	ret
	
	end
