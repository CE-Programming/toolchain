	assume	adl=1

	section	.text
	public	__bdvrms
__bdvrms:
; I: B=dividend, C=divisor
; O: a=?, h=abs(B)%abs(C), l=abs(B)/abs(C)

	push	bc

	ld	a, c
	rla
	jr	nc, .neg_divisor_skip
	xor	a, a
	sub	a, c
	ld	c, a
.neg_divisor_skip:

	ld	a, b
	rla
	jr	nc, .neg_dividend_skip
	xor	a, a
	sub	a, b
	ld	b, a
.neg_dividend_skip:

	call	__bdvrmu

	pop	bc
	ret


	extern	__bdvrmu
