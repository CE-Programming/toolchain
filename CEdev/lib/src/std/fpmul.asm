;--------------------------------------------------------------
;
;	    Code Generation Helper
;	For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;-------------------------------------------------------------------------
;	  	IEEE Single precision multiply
; Input:
;	Operand1: 
;		  AuBC : 32 bit
;
;	Operand2: 
;		  EuHL : 32 bit
;
; Output:
;	Result:   AuBC : 32 bit
; Registers Used:
;	flags
;
;-------------------------------------------------------------------------

	segment	code

	.assume adl=1
	.ref	__fpupop1, __fpupop2, __fppack
        .def    __fmul

__fmul         equ 000288h

