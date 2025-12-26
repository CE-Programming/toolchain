	.assume	adl=1

	.section	.data

	.global	_prev_reg
_prev_reg:
	;       L H U  E D U  C B U  A  X I U  Y I U
	db	0,0,0, 0,0,0, 0,0,0, 0, 0,0,0, 0,0,0

	.global	_next_reg
_next_reg:
	;       L H U  E D U  C B U  A  X I U  Y I U
	db	0,0,0, 0,0,0, 0,0,0, 0, 0,0,0, 0,0,0

	section	.text

	.local	_set_prev_reg
_set_prev_reg:
	ld	(_prev_reg +  0), hl
	ld	(_prev_reg +  3), de
	ld	(_prev_reg +  6), bc
	ld	(_prev_reg +  9), a
	; ld	(_prev_reg + 10), iy
	; ld	(_prev_reg + 13), ix
	ret

	.local	_set_next_reg
_set_next_reg:
	ld	(_next_reg +  0), hl
	ld	(_next_reg +  3), de
	ld	(_next_reg +  6), bc
	ld	(_next_reg +  9), a
	; ld	(_next_reg + 10), iy
	; ld	(_next_reg + 13), ix
	ret

	.global	_CRT_smulu_b
_CRT_smulu_b:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	a, (iy + 6)
	call	_set_prev_reg
	call	__smulu_b
	jr	_set_next_reg

	.global	_CRT_smulu_b_fast
_CRT_smulu_b_fast:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	a, (iy + 6)
	jp	__smulu_b_fast

	.global	_CRT_imulu_b
_CRT_imulu_b:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	a, (iy + 6)
	call	_set_prev_reg
	call	__imulu_b
	jr	_set_next_reg

	.global	_CRT_imulu_b_fast
_CRT_imulu_b_fast:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	a, (iy + 6)
	jp	__imulu_b_fast

	.global	_CRT_lmulu_b
_CRT_lmulu_b:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	e, (iy + 6)
	ld	a, (iy + 9)
	call	_set_prev_reg
	call	__lmulu_b
	jr	_set_next_reg

	.global	_CRT_lmulu_b_fast
_CRT_lmulu_b_fast:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	e, (iy + 6)
	ld	a, (iy + 9)
	jp	__lmulu_b_fast

	.global	_CRT_llmulu_b
_CRT_llmulu_b:
	ld	iy, 0
	add	iy, sp
	ld	l, (iy + 12)
	push	hl
	ld	hl, (iy + 3)
	ld	de, (iy + 6)
	ld	bc, (iy + 9)
	call	__llmulu_b
	ld	sp, iy
	ret

	extern	__smulu_b
	extern	__smulu_b_fast

	extern	__imulu_b
	extern	__imulu_b_fast

	extern	__lmulu_b
	extern	__lmulu_b_fast

	extern	__llmulu_b
