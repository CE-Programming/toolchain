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

__lxor         equ 0001FCh	
