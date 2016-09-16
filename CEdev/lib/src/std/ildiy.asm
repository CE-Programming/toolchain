; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer load hl,(iy+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;
; Output:
;	Result:   hl : 24 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.def __ildiy
	.assume adl=1

__ildiy		equ 00014Ch
