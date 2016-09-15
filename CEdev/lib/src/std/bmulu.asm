; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Byte Multiply
; Input:
;	Operand1: 
;		  B : 8 bit 
;
;	Operand2: 
;		  C : 8 bit 
;
; Output:
;	Result:   A : 8 bit product
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def	__bmulu
	.assume adl=1

__bmulu:
	push	bc
	mlt	bc
	ld	a,c
	pop	bc
	ret
