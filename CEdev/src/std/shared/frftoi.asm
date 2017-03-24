; (c) Copyright 2004-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; float to fract integer conversion.
;
; Input:
;	Operand1: 
;		  eHL : 32 bits
;
; Output:
;	Result:   HL : 24 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __frftoi
	.assume adl=1

__frftoi	equ 0002A8h
