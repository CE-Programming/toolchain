; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract short conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   HL : 16 bits
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frftos
	.ref	__frftous

__frftos       equ 0002B0h

