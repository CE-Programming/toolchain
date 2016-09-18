	.ref __imulu
	.ref _malloc
	.ref _memset
	.def _calloc
	.assume adl=1

_calloc:
	pop	de
	pop	bc
	pop	hl
	push	bc
	push	hl
	push	de
	call	__imulu
	push	hl
	call	_malloc
	add	hl,de 
	or	a,a 
	sbc	hl,de
	pop	bc
	ret	z
	push	bc
	ex	de,hl
	or	a,a
	sbc	hl,hl
	push	hl
	push	de
	call	_memset
	pop	hl
	pop	bc
	pop	bc
	ret
