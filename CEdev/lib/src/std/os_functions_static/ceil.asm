	.ref __frameset0
	.ref __fneg
	.ref _floor
	.def _ceil
	.assume adl=1

; double ceil(double d);

_ceil:
	call	__frameset0
	ld	bc,(ix+6)
	ld	a,(ix+9)
	call	__fneg
	ld	l,a
	ld	h,0
	push	hl
	push	bc
	call	_floor
	pop	bc
	pop	bc
	push	hl
	pop	bc
	ld	a,e
	call	__fneg
	ld	e,a
	push	bc
	pop	hl
	ld	sp,ix
	pop	ix
	ret
	