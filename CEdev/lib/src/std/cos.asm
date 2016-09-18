	.ref _sinus
	.ref __frameset0
	.ref __fcmp
	.ref __fneg
	.def _cos
	
; double cos(double arg);

_cos:
	call	__frameset0
	ld	hl,(ix+6)
	ld	e,(ix+9)
	ld	bc,0
	xor	a,a
	push	hl
	push	de
	call	__fcmp
	pop	bc
	pop	de
	ld	a,e
	jp	p,l_1
	call	__fneg

l_1:	ld	hl,1
	push	hl
	ld	l,a
	push	hl
	push	bc
	call	_sinus
	ld	sp,ix
	pop	ix
	ret
