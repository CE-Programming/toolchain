; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Multiplication Signed/Unsigned.
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1: 
;		  uHL : 24 bits
;
;	Operand2: 
;		  uBC : 24 bits
;
; Output:
;	Result:   uHL : 24 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__imulu,__imuls,__imul_b
	
__imul_b:
	push bc
	ld bc,0
	ld c,a
	call __imulu
	pop bc
	ret
	
__imuls:
__imulu:
	push	af
	push	de
	push	bc
	push	hl
	ex	de,hl
	ld	hl,2
	add	hl,sp
	ld	b,(hl)
	mlt bc
	inc	hl
	inc	hl
	inc	hl
	ld	a,d
	ld	d,(hl)
	mlt	de
	dec	hl
	ld	l,(hl)
	ld	h,a
	mlt	hl
	ld	a,l
	add	a,e
	add	a,c
	pop	de
	pop	bc
	push	bc
	or	a,a
	sbc	hl,hl
	add.s	hl,de
	ex	de,hl
	ld	h,b
	mlt	hl
	ld	b,d
	mlt	bc
	add	hl,bc
	add	a,h
	ld	h,a
	pop	bc
	ld	d,c
	mlt	de
	push	hl
	dec sp
	pop	hl
	inc	sp
	ld	l,0
	add	hl,de
	pop	de
	pop	af
	ret

