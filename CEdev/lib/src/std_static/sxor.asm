; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short XOR.
; Input:
;	Operand1: 
;		  bc : 16 bit
;
;	Operand2: 
;		  hl : 16 bit
;
; Output:
;	Result:   hl : 16 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__sxor

__sxor:
	push	af	
	
	ld	a,l
	xor	a,c
	ld	l,a

	ld	a,h
	xor	a,b
	ld	h,a

	pop	af
	ret	
	
