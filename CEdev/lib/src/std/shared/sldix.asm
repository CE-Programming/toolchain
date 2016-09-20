; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; short load hl,(ix+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;
; Output:
;       Result:   hl : 16 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.def __sldix
	.assume adl=1
	
__sldix		equ 00021Ch
