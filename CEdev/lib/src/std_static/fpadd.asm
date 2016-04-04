;--------------------------------------------------------------
;
;			Code Generation Helper
;		    For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision add
;
; INPUTS:	AuBC		OP1.
;		EuHL		OP2.
;
; OUTPUTS:	AuBC		Sum.
;
; Returns the result of adding the absolute values of the single-precision
; floating-point values OP1 and OP2.  If Sign of result is 1, the sum is
; negated before being returned.
;
;--------------------------------------------------------------

	segment	CODE
	.assume adl=1
	.ref	__fpupop1, __fpupop2, __fppack
	.def    __fadd
__fadd:
	push	hl
	push	de
	call	__fpupop1	;unpack operand 1
	rr	d		;carry = sign
	push	af		;save sign
	call	__fpupop2	;unpack operand 2
	pop	af
	rl	d		;D has both sign bits (00000021)
	rrc	d		;swap sign bit (0000021 -> 10000002)
	cp	a,e		;exp op1 < exp op2 ?
	jr	c,less		;- yes, skip

	rlc	d		;swap sign bit (1000002 -> 00000021)
	push	hl
	push	bc
	ld	b,a
	ld	a,e
	ld	e,b
	pop	hl
	pop	bc		;swap operands
less:
	sub	a,e
	jr	z,noshift

	cp	a,-24		;too much shift?
	ccf			;(reset carry if jump)
	jr	nc,noadd	;- yes, skip add

	push	ix
	push	de
	push	bc
	ld	ix,0
	add	ix,sp
	ld	d,(ix+2)
loop1:
	srl	d		;shift uBC right
	rr	b
	rr	c
	inc	a
	jr	nz,loop1

	ld	(ix),bc
	ld	(ix+2),d
	pop	bc
	pop	de
	pop	ix
noshift:
	ld	a,d
	and	a,a		;clear carry, set parity
	jp	pe,doadd	;same sign, add

	sbc	hl,bc
	sbc	a,a
	jr	common
doadd:
	add	hl,bc
noadd:
	ld	a,0
	adc	a,a
common:
	push	hl
	pop	bc
	call	__fppack				
	pop	de
	pop	hl
	ret

