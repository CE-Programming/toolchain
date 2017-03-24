; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Integer Division
; Input:
;	Operand1: 
;		  hl : 24 bits (dividend x)
; 
;	Operand2: 
;		  bc : 24 bits (divisor y)
;
; Output:
;	Result:   hl : 24 bits
;
; Registers Used:
;	a, de
;-------------------------------------------------------------------------
	.def __idivs
	.assume adl=1

__idivs		equ 00013Ch
