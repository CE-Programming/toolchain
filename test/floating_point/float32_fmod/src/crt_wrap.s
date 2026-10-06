	.assume	adl=1

	.section	.text

	.global	_frem_libcall
	.type	_frem_libcall, @function

_frem_libcall:
	ld	iy, 0
	add	iy, sp
	ld	bc, (iy + 3)
	ld	a, (iy + 6)
	ld	hl, (iy + 9)
	ld	e, (iy + 12)
	call	__frem
	push	bc
	pop	hl
	ld	e, a
	ret

	.extern	__frem
