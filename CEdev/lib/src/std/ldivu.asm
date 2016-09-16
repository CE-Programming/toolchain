; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Division Unsigned
; Input:
;	Operand1: 
;		  EuHL : 32 bits
; 
;	Operand2: 
;		  AuBC : 32 bits
; Output:
;	Result:   EuHL : 32 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __ldivu, __ldvrmu
	.assume adl=1

__ldivu        equ 0001B8h
__ldvrmu       equ 0001BCh
