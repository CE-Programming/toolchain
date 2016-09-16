	.ref __frameset
	.ref _malloc
	.ref _strlen
	.ref _strcpy
	.ref __icmpzero
	.def _strdup
	.assume adl=1

_strdup:
	ld	hl,-3
	call	__frameset
	ld	bc,(ix+6)
	push	bc
	call	_strlen
	pop	bc
	inc	hl
	push	hl
	call	_malloc
	pop	bc
	ld	(ix+-3),hl
	call	__icmpzero
	jr	z,l_1
	ld	bc,(ix+6)
	push	bc
	ld	bc,(ix+-3)
	push	bc
	call	_strcpy
	pop	bc
	pop	bc
l_1:	ld	hl,(ix+-3)
	ld	sp,ix
	pop	ix
	ret
