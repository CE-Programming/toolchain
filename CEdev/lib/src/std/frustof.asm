; (c) Copyright 2008 Zilog, Inc.
;-------------------------------------------------------------------------
; fract unsigned short to float conversion.
;
; Input:
;	Operand1: 
;		  HL : 16 bits
;
; Output:
;	Result:   eHL : 32 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __frustof
	.assume adl=1
	
__frustof	equ 0002C8h
