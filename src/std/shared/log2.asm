	.def _log2
	.ref _log
	.ref __fdiv
	.ref __frameset0
	.assume adl=1

_log2:
	call	__frameset0
	ld	c,(ix+9)
	ld	b,0
	push	bc
	ld	bc,(ix+6)
	push	bc
	call	_log
	push	hl
	pop	bc
	ld	a,e
	ld	hl,3240472
	ld	e,63
	call	__fdiv
	ld	e,a
	push	bc
	pop	hl
	ld	sp,ix
	pop	ix
	ret
