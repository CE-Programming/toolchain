	assume	adl=1

	section	.text

	public	_f64_pos_zero
_f64_pos_zero:
	db $00, $00, $00, $00, $00, $00, $00, $00

	public	_f64_neg_zero
_f64_neg_zero:
	db $00, $00, $00, $00, $00, $00, $00, $80

	public	_f64_pos_one
_f64_pos_one:
	db $00, $00, $00, $00, $00, $00, $F0, $3F

	public	_f64_neg_one
_f64_neg_one:
	db $00, $00, $00, $00, $00, $00, $F0, $BF

	public	_f64_pos_pi
_f64_pos_pi:
	db $18, $2D, $44, $54, $FB, $21, $09, $40

	public	_f64_neg_pi
_f64_neg_pi:
	db $18, $2D, $44, $54, $FB, $21, $09, $C0

	public	_drem_libcall
_drem_libcall:
	call	__frameset0
	; push y onto the stack
	ld	hl, (ix + 21)
	push	hl
	ld	hl, (ix + 18)
	push	hl
	ld	hl, (ix + 15)
	push	hl
	; load x in registers
	ld	bc, (ix + 12)
	ld	de, (ix + 9)
	ld	hl, (ix + 6)
	call	__drem
	ld	sp, ix
	pop	ix
	ret

	extern	__drem
	extern	__frameset0
