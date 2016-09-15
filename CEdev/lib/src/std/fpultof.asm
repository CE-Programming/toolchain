;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Unsigned long to IEEE Single precision.
;
; INPUTS:
;		abc:	32-bit unsigned long
;
; OUTPUTS:
;		abc:	IEEE Single precision.
;
;--------------------------------------------------------------

	segment	CODE
	.assume	adl=1
	.ref	__fppack
        .def    __ultof
	
__ultof        equ 000280h

	end
