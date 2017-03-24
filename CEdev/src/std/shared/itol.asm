; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Integer to Long conversion
; Input:
;	Operand1: 
;                 BC : 24 bit
;
; Output:
;       Result:   A:BC : 32 bit
; Registers Used:
;       
;-------------------------------------------------------------------------
	.def __itol
	.assume adl=1
	
__itol		equ 000194h
