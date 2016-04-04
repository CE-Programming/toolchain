;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Pack IEEE operand of dyadic operations.
;
; INPUTS:		
;		AuBC:		2s-comp mantissa+fraction (9+23 bit)
;		E:		Exponent.
;		D:		Sign.
;
; OUTPUTS:	AuBC:		32 bit IEEE float.
; 
;		A AAAAAAB  BBBBBBBBBBBBBBCCCCCCCCC
;		S EEEEEEE  FFFFFFFFFFFFFFFFFFFFFFF
;		0 1     8  9                     31
; MODIFIES:	
;	flags
;--------------------------------------------------------------

	segment	code
	.assume adl=1
	.def	__fppack

__fppack:
	push	hl
	push	de
	rr	d		;carry = sign bit
	push	af		;save sign bit
	ld	d,0
	or	a,a		;clear carry
	ld	hl,0
	adc	hl,bc		;zero?
	jr	nz,nouflow	;- no, skip

	cp	a,1		;all zero?
	jr	nc,nouflow	;- no, skip
xflow:
	ccf			;set carry if overflow, else underflow
	sbc	a,a		;-1 if carry, else 0
	sbc	hl,hl		;-1 if carry, else 0
	ld e,0			; CR 3938
	pop af
	jr exit1
	
nouflow:
	or	a,a		;positive?
	jp	p,noneg		;- yes, skip

	pop	af		;restore sign
	ccf			;invert sign
	push	af		;save sign
	or a,a		;CR 3936+
	ld	hl,0
	sbc	hl,bc
	ld	c,a
	ld	a,0
	sbc	a,c
noneg:
	jr	z,noshift	;skip if A is zero

	push	af		;save xAF
	inc	sp		;skip over flags
	push	hl		;save uHL
	ld	a,l		;save low-order byte
	ld	hl,8
	add	hl,de
	ex	de,hl		;adjust exponent
	inc	sp		;skip over low-order byte
	pop	hl		;effectively shift right one byte
	inc	sp		;skip over garbage
noshift:
	or	a,a		;clear carry
	ld	bc,0
	adc	hl,bc
	jp	m,norotate

	inc	bc		;BC = 1
loop1:
	ex	de,hl
	sbc.s	hl,bc		;decrement exponent	;CR 3936
	ex	de,hl
	jr	c,xflow		;exit if underflow

	add	a,a
	adc	hl,hl
	jp	p,loop1
norotate:
	add	a,a		;get rounding bit
	ld	bc,800000H	;this constant used several places
	adc	hl,bc		;round, invert high-order bit
	jp	p,noadj		;skip if rounding does not oflow

	inc	de		;adjust exp. (minus implies uHL == 800000)
	add	hl,bc		;clear high-order bit
noadj:
	ld	a,d		;get possible exponent oflow
	cp	a,1		;exponent overflow?
	jr	nc,xflow	;- yes, exit

	pop	af		;carry = sign bit
	rr	e		;set up sign bit, exponent
	jr	nc,exit1	;skip if no low-order bit

	add	hl,bc		;set high-order bit
exit1:
	ld	a,e
	push	hl
	pop	bc
	pop	de
	pop	hl
	ret

