; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; short load hl,(iy+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;
; Output:
;       Result:   hl : 16-bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __sldiy
	
__sldiy        equ 000220h

