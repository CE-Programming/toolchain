; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Subtract Op1 - Op2
; Input:
;	Operand1: 
;                 EHL : 32 bits
;		  
;	Operand2: 
;                 ABC : 32 bits
;
; Output:
;	Result:   EHL :	 32 bits
; Registers Used:
;	flags
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __lsub

__lsub         equ 0001F8h

