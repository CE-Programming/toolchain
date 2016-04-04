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
	
__ultof:	
	push	de		; (ix-3)
	ld	d,0		; sign bit
	ld	e,7FH+23
	call	__fppack
	pop	de
	ret
	end
