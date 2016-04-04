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

__fdiv:
	push	ix
	push	iy
	push	hl
	push	de
	call	__fpupop1	;unpack dividend
	jr	z,exit3		;skip if zero to avoid loop

	push	bc		;save dividend
	ld	c,a		;save exponent
	ld	a,d		;save sign
	call	__fpupop2	;unpack divisor
	push	hl		;save divisor
	push	af		;save zero indication
	xor	a,d		;compute result sign
	ld	b,0
	ld	d,0
	ld	hl,7FH+24-1
	add	hl,bc
	sbc	hl,de		;compute result exponent
	push	hl
	pop	ix
	ld	d,a		;save result sign
	pop	af
	pop	bc		;restore divisor
	pop	hl		;restore dividend
	jr	z,oflow		;skip if divisor zero

	ld	iy,0
	or	a		;clear carry
loop1:
	rla			;save HL shift overflow
	add	iy,iy		;shift quotient left
	jr	c,exit1		;exit loop when IY overflow

	sbc	hl,bc
	jr	nc,over

	sra	a		;restore HL shift overflow
	jr	c,over

	add	hl,bc		;restore dividend
	jr	under
over:
	inc	iy		;update quotient
under:
	dec	ix		;update exponent
	add	hl,hl		;shift dividend left, including carry
	jr	loop1
exit1:
	ld	e,0
	sra	a		;restore carry
	jr	c,round		;round if HL shift overflow

	or	a		;clear carry
	sbc	hl,bc		;round ?
	jr	c,skip1		;- no, skip
round:
	ld	bc,1
	add	iy,bc		;round
	rl	e		;save any overflow
skip1:
	inc	e		;EuIY = quotient
	ld	a,ixh
	or	a,a		;high-order exponent zero?
	jr	z,skip2		;- yes, skip

	jp	m,uflow		;skip if underflow
oflow:
	scf			;set carry for overflow
uflow:
	sbc	hl,hl		;0 for uflow, -1 for oflow
	ld	e,h		;ditto
	ld	a,0
	push	hl
	jr	exit2
skip2:
	ld	a,e		;AuIY = quotient
	ld	e,ixl		;set exponent
	push	iy
exit2:
	pop	bc		;AuBC = quotient
exit3:
	call	__fppack
	pop	de
	pop	hl
	pop	iy
	pop	ix
	ret

