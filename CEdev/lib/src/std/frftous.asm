; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract unsigned short conversion.
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
	.def	__frftous

__frftous      equ 0002B4h
