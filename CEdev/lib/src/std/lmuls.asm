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
	.def __lmuls
	.assume adl=1

__lmuls		equ 0001C8h
