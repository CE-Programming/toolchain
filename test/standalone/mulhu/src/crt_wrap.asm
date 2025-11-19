	assume	adl=1

	section	.data

	public	_prev_reg
_prev_reg:
	;       L H U  E D U  C B U  A  Y I U  X I U
	db	0,0,0, 0,0,0, 0,0,0, 0, 0,0,0, 0,0,0

	public	_next_reg
_next_reg:
	;       L H U  E D U  C B U  A  Y I U  X I U
	db	0,0,0, 0,0,0, 0,0,0, 0, 0,0,0, 0,0,0

	section	.text

	private	_set_prev_reg
_set_prev_reg:
	ld	(_prev_reg +  0), hl
	ld	(_prev_reg +  3), de
	ld	(_prev_reg +  6), bc
	ld	(_prev_reg +  9), a
	ld	(_prev_reg + 10), iy
	ld	(_prev_reg + 13), ix
	ret

	private	_set_next_reg
_set_next_reg:
	ld	(_next_reg +  0), hl
	ld	(_next_reg +  3), de
	ld	(_next_reg +  6), bc
	ld	(_next_reg +  9), a
	ld	(_next_reg + 10), iy
	ld	(_next_reg + 13), ix
	ret

	public	_CRT_smulhu
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
	jq	_set_next_reg

	public	_CRT_smulhs
_CRT_smulhs:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	b, (iy + 10)
	ld	c, (iy + 9)
	ld	h, (iy + 7)
	ld	l, (iy + 6)
	pop	iy
	call	_set_prev_reg
	call	__smulhs
	jq	_set_next_reg

	public	_CRT_imulhu
_CRT_imulhu:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)
	ld	bc, (iy + 9)
	pop	iy
	call	_set_prev_reg
	call	__imulhu
	jq	_set_next_reg

	public	_CRT_imulhs
_CRT_imulhs:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)
	ld	bc, (iy + 9)
	pop	iy
	call	_set_prev_reg
	call	__imulhs
	jq	_set_next_reg

	public	_CRT_lmulhu
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
	jq	_set_next_reg

	public	_CRT_lmulhs
_CRT_lmulhs:
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)
	ld	e, (iy + 9)
	ld	bc, (iy + 12)
	ld	a, (iy + 15)
	pop	iy
	call	_set_prev_reg
	call	__lmulhs
	jq	_set_next_reg

	public	_CRT_i48mulhu
_CRT_i48mulhu:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	de, (iy + 6)
	ld	bc, (iy + 9)
	ld	iy, (iy + 12)
	call	_set_prev_reg
	call	__i48mulhu
	jq	_set_next_reg

	public	_CRT_i48mulhs
_CRT_i48mulhs:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	de, (iy + 6)
	ld	bc, (iy + 9)
	ld	iy, (iy + 12)
	call	_set_prev_reg
	call	__i48mulhs
	jq	_set_next_reg

	public	_CRT_llmulhu
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
	jq	_set_next_reg

	public	_CRT_llmulhs
_CRT_llmulhs:
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
	call	__llmulhs
	ld	sp, iy
	jq	_set_next_reg

	extern	__smulhu
	extern	__imulhu
	extern	__lmulhu
	extern	__i48mulhu
	extern	__llmulhu

	extern	__smulhs
	extern	__imulhs
	extern	__lmulhs
	extern	__i48mulhs
	extern	__llmulhs
