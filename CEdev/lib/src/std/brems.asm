; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Byte Modulus
; Input:
;	Operand1: 
;		  A : 8 bit dividend (numerator)
;
;	Operand2: 
;		  C : 8 bit divisor (denominator)
;
; Output:
;	Result:   A : 8 bit modulus
; Registers Used:
;	
;-------------------------------------------------------------------------
	.def	__brems
	.ref	__bremu
	.assume adl=1

__brems:
	push	bc
;	push	af
	ld	b,a
	bit	7,c
	jr	z,skip1
	ld	a,c
	neg
	ld	c,a
skip1:
	ld	a,b
	bit	7,a
	jr	z,skip2
	neg
skip2:
	call	__bremu
	bit	7,b
	jr	z,skip3
	neg
skip3:
;	ld	c,a
;	pop	af
;	ld	a,c
	pop	bc
	ret
