	.def _finite
	.assume adl=1

; int finite(double n);

_finite:
	pop	bc
	pop	hl
	pop	de
	push	de
	push	hl
	push	bc
	add	hl,hl
	ld	a,e
	rla
	add	a,1
	sbc	hl,hl
	inc	hl
	ret
