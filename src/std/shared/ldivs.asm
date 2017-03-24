; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Division Signed
; Input:
;	Operand1: 
;		  eHL : 32 bits
; 
;	Operand2: 
;		  aBC :	 32 bits
; Output:
;	Result:   eHL : 24 bits
;
; Registers Used:
;	
;-------------------------------------------------------------------------
	.def __ldivs
	.assume adl=1

__ldivs		equ 0001B4h
