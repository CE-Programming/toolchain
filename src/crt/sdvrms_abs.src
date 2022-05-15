	assume	adl=1

	section	.text
	public	__sdvrms_abs
__sdvrms_abs:
; I: HL=dividend, BC=divisor
; O: ude=abs(HL)/abs(BC), uhl=abs(HL)%abs(BC), sf=(HL<0)^(BC<0), cf=HL<0

	push	bc

	ld	e, a
	ld	a, h
	xor	a, b
	ld	a, h
	rla
	ld	a, e
	push	af

	jr	nc, .neg_dividend_skip
	add	hl, de
	ex	de, hl
	or	a, a
	sbc	hl, de
.neg_dividend_skip:

	ld	a, b
	rla
	jr	nc, .neg_divisor_skip
	xor	a, a
	sub	a, c
	ld	c, a
	sbc	a, a
	sub	a, b
	ld	b, a
.neg_divisor_skip:

	pop	af
	call	__sdvrmu

	pop	bc
	ret


	extern	__sdvrmu
