	assume	adl=1

	section	.text
	public	__bdvrms_abs
__bdvrms_abs:
; I: C=divisor, L=dividend
; O: a=?, h=abs(L)%abs(C), l=abs(L)/abs(C)

	ld	a, l
	public	__bdvrms_abs.hijack_a_l_dividend
.hijack_a_l_dividend:
	rla
	jr	nc, .neg_dividend_skip
	xor	a, a
	sub	a, l
	ld	l, a
.neg_dividend_skip:

	push	bc

	ld	a, c
	rla
	jr	nc, .neg_divisor_skip
	xor	a, a
	sub	a, c
	ld	c, a
	jr	nc, .neg_dividend_skip
.neg_divisor_skip:

	call	__bdvrmu.hijack_l_dividend

	pop	bc
	ret


	extern	__bdvrmu.hijack_l_dividend
