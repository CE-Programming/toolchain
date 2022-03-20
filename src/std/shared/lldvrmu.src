	assume	adl=1

	section	.text
	public	__lldvrmu
__lldvrmu:
; Atrociously slow.

	ld	iy, 5
	add	iy, sp
	public	__lldvrmu.hijack
.hijack:

	ld	a, i
	di
	push	af

	push	bc
	push	de
	push	hl
; Stack frame:
; iy - 17 -> dividend
; iy - 14 -> dividend >> 24
; iy - 11 -> dividend >> 48
; iy -  8 -> interrupts state
; iy -  5 -> return vector
; iy -  2 -> ???
; iy +  1 -> ???
; iy +  4 -> ???
; iy +  7 -> divisor
; iy + 10 -> divisor >> 24
; iy + 13 -> divisor >> 48

	ld	bc, (iy + 10)
	sbc	hl, hl
	ex	de, hl
	sbc	hl, hl
	exx
	ld	hl, (iy + 13)
	ex.s	de, hl
	ld	hl, (iy + 7)
	ld	sp, hl
	sbc	hl, hl

	ld	c, 8

.byte_loop:
	dec	iy
	ld	a, (iy - 9)

	ld	b, 8

.bit_loop:
	adc	a, a
	exx
	adc	hl, hl
	ex	de, hl
	adc	hl, hl
	ex	de, hl
	exx
	adc	hl, hl

	exx
	sbc	hl, sp
	ex	de, hl
	sbc	hl, bc
	ex	de, hl
	exx
	sbc	hl, de

	jr	nc, .add_back_skip
	exx
	add	hl, sp
	ex	de, hl
	adc	hl, bc
	ex	de, hl
	exx
	adc	hl, de
.add_back_skip:

	djnz	.bit_loop

	adc	a, a
	cpl
	ld	(iy + 15), a

	dec	c
	jr	nz, .byte_loop

	ld	sp, iy
; Stack frame:
; iy      -> interrupts state
; iy +  3 -> return vector
; iy +  6 -> ???
; iy +  9 -> ???
; iy + 12 -> ???
; iy + 15 -> quotient
; iy + 18 -> quotient >> 24
; iy + 21 -> quotient >> 48

	push	hl
	exx
	pop	bc

	pop	af
	ret	po
	ei
	ret
