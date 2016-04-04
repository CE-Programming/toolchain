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

	segment	CODE
	.assume	adl=1

	.ref	__fppack
        .def    __ltof

__ltof:
	push	de
	ld	de,7FH+23
	or	a,a
	jp	p,plus

	push	hl
	ld	hl,0
	sbc	hl,bc
	push	hl
	pop	bc
	pop	hl
	ld	d,a
	ld	a,0
	sbc	a,d
	jp	p,notmin	;skip if now positive

	srl	a		;was/is 80000000H, adjust mantissa = 40000000H
	inc	e		;adjust exponent
notmin:
	ld	d,1		; sign bit
plus:
	call	__fppack
	pop	de
	ret

