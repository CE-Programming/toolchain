; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Shift Left
; Input:
;	Operand1: 
;		  BC : 16 bit number of bits to shift
;			Assume B=0 C=shift count
;	Operand2: 
;		  HL : 16 bit value to be shifted by C
;
; Output:
;	Result:   HL : 16 bit 
; Registers Used:
;	none
; Comments:
;       Created 12/2001: G.Loegel
;-------------------------------------------------------------------------
	.def __sshl, __sshl_b
	.assume adl=1

__sshl_b	equ 000244h
__sshl		equ 000240h
