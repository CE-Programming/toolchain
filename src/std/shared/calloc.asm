	.ref __imulu
	.ref _malloc
	.ref _memset
	.def _calloc
	.assume adl=1

_calloc:
	pop	de
	pop	bc
	pop	hl
	push	hl
	push	bc
	push	de
	call	__imulu
	push	hl
	call	_malloc
	add	hl,de
	xor	a,a
	sbc	hl,de
	ld	e,a
	push	de
	push	hl
	call	nz,_memset
	pop	hl
	pop	de
	pop	bc
	ret
