;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Negate.
;
; INPUTS:
;		AuBC:	32-bit IEEE Single Precision.
;
; OUTPUTS:
;		AuBC:	32-bit IEEE Single Precision.
;
;--------------------------------------------------------------

	segment	CODE
	.assume adl=1
	.def	__fneg
__fneg:
	cp a,00h
	jr nz, __noexit
	push hl
	ld	hl,0
	xor	a,a
	sbc	hl,bc
	pop	hl
	jr	z, __exit
__noexit:
	xor	a,80H
__exit:
	ret	
	end

