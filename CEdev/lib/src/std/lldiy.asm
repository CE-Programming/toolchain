; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; long load e:hl,(iy+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;
; Output:
;       Result:   E:HL : 32 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __lldiy
	
__lldiy        equ 0001C4h

