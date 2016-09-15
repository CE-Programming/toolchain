; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract char conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   A : 8 bits
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__frftob
	.ref	__frftoub

__frftob       equ 0002A0h

