	.assume	adl=1

	.section	.data._prev_reg

	.global	_prev_reg
_prev_reg:
	;	L H U  E D U  C B U  A  Y I U  X I U
	db	0,0,0, 0,0,0, 0,0,0, 0, 0,0,0, 0,0,0

	.section	.data._next_reg

	.global	_next_reg
_next_reg:
	;	L H U  E D U  C B U  A  Y I U  X I U
	db	0,0,0, 0,0,0, 0,0,0, 0, 0,0,0, 0,0,0

	.section	.text

	.local	_set_prev_reg
_set_prev_reg:
	ld	(_prev_reg +  0), hl
	ld	(_prev_reg +  3), de
	ld	(_prev_reg +  6), bc
	ld	(_prev_reg +  9), a
	ld	(_prev_reg + 10), iy
	ld	(_prev_reg + 13), ix
	ret

	.local	_set_next_reg
_set_next_reg:
	ld	(_next_reg +  0), hl
	ld	(_next_reg +  3), de
	ld	(_next_reg +  6), bc
	ld	(_next_reg +  9), a
	ld	(_next_reg + 10), iy
	ld	(_next_reg + 13), ix
	ret

	.global	_CRT_smulhu
_CRT_smulhu:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	b, (iy + 10)
	ld	c, (iy + 9)
	ld	h, (iy + 7)
	ld	l, (iy + 6)
	pop	iy
	call	_set_prev_reg
	call	__smulhu
	jp	_set_next_reg

	.global	_CRT_imulhu
_CRT_imulhu:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)
	ld	bc, (iy + 9)
	pop	iy
	call	_set_prev_reg
	call	__imulhu
	jp	_set_next_reg

	.global	_CRT_lmulhu
_CRT_lmulhu:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)
	ld	e, (iy + 9)
	ld	bc, (iy + 12)
	ld	a, (iy + 15)
	pop	iy
	call	_set_prev_reg
	call	__lmulhu
	jp	_set_next_reg

	.global	_CRT_i48mulhu
_CRT_i48mulhu:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	de, (iy + 6)
	ld	bc, (iy + 9)
	ld	iy, (iy + 12)
	call	_set_prev_reg
	call	__i48mulhu
	jp	_set_next_reg

	.global	_CRT_llmulhu
_CRT_llmulhu:
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
	call	_set_prev_reg
	call	__llmulhu
	ld	sp, iy
	jp	_set_next_reg

	.extern	__smulhu
	.extern	__imulhu
	.extern	__lmulhu
	.extern	__i48mulhu
	.extern	__llmulhu
