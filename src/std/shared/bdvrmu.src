	assume	adl=1

	section	.text
	public	__bdvrmu
__bdvrmu:
; I: B=dividend, C=divisor
; O: a=?, b=0, h=B%C, l=B/C

	ld	l, b
	public	__bdvrmu.hijack_l_dividend
.hijack_l_dividend:
	ld	h, 0

	ld	b, 8

.loop:
	add	hl, hl

	ld	a, h
	sub	a, c

	jr	c, .bit_skip
	ld	h, a
	inc	l
.bit_skip:

	djnz	.loop

	ret
