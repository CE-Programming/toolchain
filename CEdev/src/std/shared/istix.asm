; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer store (ix+nnnnnn),HL
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;                 HL : 24-bit integer to store
;
; Output:
;       
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.def __istix
	.assume adl=1

__istix		equ 00018Ch
