; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Indirect Call 
; Input:
;	Operand1: 
;                 iy : 24 bit
;
; Output:
; Registers Used:
;-------------------------------------------------------------------------
	.def __indcall
	.assume adl=1

__indcall	equ 00015Ch
