;--------------------------------------------------------------
;
;			Code Generation Helper
;		    For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Signed long to IEEE Single precision.
;
; INPUTS:	AuBC 32-bit	signed long.
;
; OUTPUTS:	AuBC 32-bit	IEEE Single precision.
;
;--------------------------------------------------------------
	.def __ltof
	.assume	adl=1

__ltof		equ 000284h
