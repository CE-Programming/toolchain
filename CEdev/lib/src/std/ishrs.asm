; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Shift Right Signed
; Input:
;	Operand1: 
;		  BC : 24 bit number of bits to shift
;			Assume B=0 C=shift count
;	Operand2: 
;		  HL : 24 bit value to be shifted by C
;
; Output:
;	Result:   HL : 24 bit 
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __ishrs, __ishrs_b
	.assume adl=1

__ishrs_b	equ 000180h
__ishrs		equ 00017Ch
