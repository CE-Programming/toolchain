;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision to long.
;
; INPUTS:	abc:	32-bit	IEEE Single precision.
;
; OUTPUTS:	abc:	32-bit	signed long.
;
;--------------------------------------------------------------

	segment	CODE
	.assume adl=1
	
	.ref	__fpupop1, __lshrs, __lshl
        .def    __ftol

__ftol         equ 00027Ch

	end
