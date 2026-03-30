	.assume	adl=1

	.section	.text

	.global	_crt_fcmp
	.type	_crt_fcmp, @function
_crt_fcmp:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	e, (iy + 6)
	ld	bc, (iy + 9)
	ld	a, (iy + 12)
	call	__fpcmp
	push	af
	pop	hl
	ld	a, l
	ret
	.extern	__fpcmp

	.global	_crt_fcmpo
	.type	_crt_fcmpo, @function
_crt_fcmpo:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	e, (iy + 6)
	ld	bc, (iy + 9)
	ld	a, (iy + 12)
	call	__fpcmpo
	push	af
	pop	hl
	ld	a, l
	ret
	.extern	__fpcmpo

	.global	_crt_fcmpu
	.type	_crt_fcmpu, @function
_crt_fcmpu:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	e, (iy + 6)
	ld	bc, (iy + 9)
	ld	a, (iy + 12)
	call	__fpcmpu
	push	af
	pop	hl
	ld	a, l
	ret
	.extern	__fpcmpu

	.global	_crt_dcmp
	.type	_crt_dcmp, @function
_crt_dcmp:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 18)
	push	hl
	ld	hl, (iy + 15)
	push	hl
	ld	hl, (iy + 12)
	push	hl
	ld	bc, (iy + 9)
	ld	de, (iy + 6)
	ld	hl, (iy + 3)
	call	__dcmp
	push	af
	pop	hl
	ld	a, l
	ld	sp, iy
	ret
	.extern	__dcmp

	.global	_crt_dcmpo
	.type	_crt_dcmpo, @function
_crt_dcmpo:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 18)
	push	hl
	ld	hl, (iy + 15)
	push	hl
	ld	hl, (iy + 12)
	push	hl
	ld	bc, (iy + 9)
	ld	de, (iy + 6)
	ld	hl, (iy + 3)
	call	__dcmpo
	push	af
	pop	hl
	ld	a, l
	ld	sp, iy
	ret
	.extern	__dcmpo

	.global	_crt_dcmpu
	.type	_crt_dcmpu, @function
_crt_dcmpu:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 18)
	push	hl
	ld	hl, (iy + 15)
	push	hl
	ld	hl, (iy + 12)
	push	hl
	ld	bc, (iy + 9)
	ld	de, (iy + 6)
	ld	hl, (iy + 3)
	call	__dcmpu
	push	af
	pop	hl
	ld	a, l
	ld	sp, iy
	ret
	.extern	__dcmpu
