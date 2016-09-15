; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long OR.
; Input:
;	Operand1: 
;		 ehl  : 32 bit
;
;	Operand2: 
;		  abc : 32 bit
;
; Output:
;	Result:   ehl : 32 bit
; Registers Used:
;	
;-------------------------------------------------------------------------
	.assume adl=1
	.def    __lor
	.ref	__ior

__lor          equ 0001D8h

