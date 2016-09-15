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
	.assume adl=1
	.def	__imuls

__imuls        equ 000154h
