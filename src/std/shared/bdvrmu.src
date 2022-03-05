	assume	adl=1

	section	.text
	public	__bdvrmu
__bdvrmu:
; I: B=dividend, C=divisor
; O: a=B%C, b=0, h=?, l=B/C

	ld	l, b
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
