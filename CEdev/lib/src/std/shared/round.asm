	.def _round
	.ref __frameset0
	.ref __fcmp
	.ref __fadd
	.ref __fsub
	.ref _floor
	.ref _ceil
	.assume adl=1
	
_round:
	call	__frameset0
	ld	hl,(ix+6)
	ld	e,(ix+9)
	ld	bc,0
	xor	a,a
	call	__fcmp
	push	af
	or	a,a
	sbc	hl,hl
	ld	e,63
	ld	bc,(ix+6)
	pop	af
	ld	a,(ix+9)
	jp	m,IsLessZero
	call	__fadd
	or	a,a
	sbc	hl,hl
	ld	l,a
	push	bc
	push	hl
	call	_floor
	jr	Finish
IsLessZero:
	call	__fsub
	or	a,a
	sbc	hl,hl
	ld	l,a
	push	bc
	push	hl
	call	_ceil
Finish:
	ld	sp,ix
	pop	ix
	ret
