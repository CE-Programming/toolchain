; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long OR.
; Input:
;	Operand1: 
;		 ehl  : 32 bit
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
    .def    __lor
	.ref	__ior

__lor:
	call	__ior		;OR HL, BC
	push	af			;save a
	or		a,	e
	ld		e,	a		;OR E, A
	pop		af			;restore a

	ret	

