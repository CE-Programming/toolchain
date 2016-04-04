; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Multiplication Signed/Unsigned.
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1: 
;		  EuHL : 32 bits
;
;	Operand2: 
;		  AuBC : 32 bits
;
; Output:
;	Result:   EuHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lmulu,__lmuls

__lmuls:
__lmulu:
	push	af
	push	de
	push	bc
	push	hl

	ld		h, l
	ld		l, a
	mlt		hl
	ld		a, l		;a = dw
	ld		h, e
	ld		l, c
	mlt		hl
	add		a, l		;a = dw+az
	ld		hl, 1
	add		hl, sp
	ld		d, (hl)
	inc		hl
	ld		b, (hl)
	inc		hl
	inc		hl
	ld		c, (hl)
	inc		hl
	ld		e, (hl)
	mlt		bc
	add		a, c		;a = dw+az+by
	mlt		de
	add		a, e		;a = dw+az+by+cx

	ex		de, hl
	pop		hl
	push	hl
	ex		de, hl
	ld		c, (hl)
	ld		b, e
	mlt		bc
	dec		hl
	ld		e, (hl)
	mlt		de
	ex		de, hl
	add		hl, bc
	ex		de, hl		;de = cy+dx
	dec		hl
	ld		c, (hl)
	dec		hl
	ld		b, (hl)
	mlt		bc
	ex		de, hl
	add		hl, bc
	ex		de, hl		;de = cy+dx+bz
	push	de

	inc		hl
	ld		bc, (hl)
	dec		hl
	dec		hl
	ld		d, (hl)
	ld		e, c
	mlt		de
	dec		hl
	ld		c, b
	ld		b, (hl)
	mlt		bc
	ex		de, hl
	add		hl, bc
	ex		de, hl		;de = cz+dy

	ld		b, (hl)
	inc		hl
	inc		hl
	inc		hl
	ld		c, (hl)
	mlt		bc			;bc = dz

	or		a, a
	sbc		hl, hl
	ld		l, b
	add		hl, de
	ld		b, l
	dec		sp
	push	hl
	inc		sp
	pop		hl
	pop		de
	add		hl, de
	add		a, h
	push	hl
	dec		sp
	dec		sp
	pop		hl
	inc		sp
	inc		sp
	ld		h, b
	ld		l, c		;HL = LB

	pop		bc
	pop		bc
	pop		de
	ld		e, a		;e = UB
	pop		af

	ret

