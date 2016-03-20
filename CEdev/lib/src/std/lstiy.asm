; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; long store (iy+nnnnnn),E:HL
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;                 E:HL : 32-bit value
;
; Output:
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __lstiy
	
__lstiy        equ 0001F4h

