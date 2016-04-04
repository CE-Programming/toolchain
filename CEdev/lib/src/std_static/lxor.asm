; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long XOR.
; Input:
;	Operand1: 
;		  ehl : 32 bit
;
;	Operand2: 
;		  abc : 32 bit
;
; Output:
;	Result:   ehl : 32 bit
; Registers Used:
;	
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lxor
	.ref	__ixor

__lxor:
	call	__ixor		;XOR HL, BC
	push	af			;save a
	xor		a,	e
	ld		e,	a		;XOR E, A
	pop		af			;restore a

	ret	
