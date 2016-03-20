; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract unsigned integer conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   HL : 24 bits
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frftoui

__frftoui      equ 0002ACh
