; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer load hl,(ix+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;
; Output:
;	Result:   hl : 24 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.def __ildix
	.assume adl=1
	
__ildix		equ 000148h
