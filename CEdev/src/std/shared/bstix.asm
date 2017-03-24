; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; byte store (ix+nnnnnn),A
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;                 A  : 8-bit integer to store
;
; Output:
;       none
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __bstix
	.assume adl=1

__bstix		equ 00010Ch

