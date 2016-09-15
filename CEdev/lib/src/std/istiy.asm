; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer store (iy+nnnnnn),HL
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;                 HL : 24-bit integer to store
;
; Output:
;       
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __istiy
	
__istiy        equ 000190h
