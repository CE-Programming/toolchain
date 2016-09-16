; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Multiplication Signed.
; Input:
;	Operand1: 
;		  BC : 24 bits
;
;	Operand2: 
;		  HL : 24 bits
;
; Output:
;	Result:   hl : 24 bit
; Registers Used:
;	de,af
;-------------------------------------------------------------------------	
	.def __imuls
	.assume adl=1

__imuls		equ 000154h
