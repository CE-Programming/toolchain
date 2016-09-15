; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Multiplication Signed.
; Input:
;	Operand1: 
;		  ABC : 32 bits 
;
;	Operand2: 
;		  EHL : 32 bits 
;
; Output:
;	Result:   ABC : 32 bit
; Registers Used:
;	de,af
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__lmuls
	.ref	__lmulu
	
__lmuls        equ 0001C8h
