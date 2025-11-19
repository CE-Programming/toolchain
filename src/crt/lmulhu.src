	assume	adl=1

	section	.text

	public	__lmulhu

; E:UHL = ((uint64_t)E:UHL * (uint64_t)A:UBC) >> 32
__lmulhu:
	push	iy
	push	de
	ld	iy, 0
	push	iy
	ld	iyl, a
	push	iy
	push	bc
	ld	iyl, iyh	; ld iy, 0
	lea	bc, iy
	inc	de
	dec.s	de
	ld	d, b
	call	__llmulu
	; E   = B
	; UHL = C
	; H   = UDE
	; L   = D
	add	iy, sp
	push	de
	ld	e, (iy - 1)	; H = UDE
	ld	(iy - 1), c	; UHL = C
	pop	hl		; UHL = C
	ld	h, e		; H = UDE
	ld	l, d		; L = D
	ld	iyl, b		; E = B
	pop	bc
	pop	de		; reset SP
	pop	de		; reset SP
	pop	de
	ld	e, iyl		; E = B
	pop	iy
	ret

	extern	__llmulu
