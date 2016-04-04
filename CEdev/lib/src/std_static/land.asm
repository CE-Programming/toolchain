; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long AND.
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

;-------------------------------------------------------------------------
	.assume adl=1
	.def	__land
	.ref	__iand

__land:
	call	__iand		;AND HL, BC
	push	af			;save a
	and		a,	e
	ld		e,	a		;AND E, A
	pop		af			;restore a

	ret	

