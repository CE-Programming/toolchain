; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; short store (iy+nnnnnn),HL
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;                 HL : 16-bit integer to store
;
; Output:
;       
;
; Registers Used:
;      
;-------------------------------------------------------------------------
        .def __sstiy
	.assume adl=1
	
__sstiy		equ 00025Ch

