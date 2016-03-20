;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision division
;
; INPUTS:
;	Operand1: 
;		  AuBC : 32 bit IEEE format
;
;	Operand2: 
;		  EuHL : 32 bit IEEE format divisor
;
; OUTPUTS:
;	Result:   AuBC : 32 bit IEEE Quotient.
; Registers Used:
;	flags
;
;--------------------------------------------------------------

	segment	code

	.assume adl=1
	.ref	__fpupop1, __fpupop2, __fppack
        .def    __fdiv

__fdiv         equ 000278h