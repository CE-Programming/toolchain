;--------------------------------------------------------------
;
;	    Code Generation Helper
;	For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc. 
;
;--------------------------------------------------------------
;-------------------------------------------------------------------------
;	  	IEEE Single precision multiply
; Input:
;	Operand1: 
;		  AuBC : 32 bit
;
;	Operand2: 
;		  EuHL : 32 bit
;
; Output:
;	Result:   AuBC : 32 bit
; Registers Used:
;	flags
;
;-------------------------------------------------------------------------

	segment	code

	.assume adl=1
	.ref	__fpupop1, __fpupop2, __fppack
        .def    __fmul

__fmul:
	push	ix
	push	hl
	push	de
	ld	ix,0
	add	ix,sp
	call	__fpupop1	;Unpack operand 1.
	push	bc		;uBC in (IX-3)
	ld	c,a		;save exponent
	ld	a,d		;save sign
	call	__fpupop2	;Unpack operand 2.
	push	hl		;uHL in (IX-6)
	xor	a,d		;compute result sign
	ld	b,0
	ld	d,0
	ld	hl,-7FH-1
	add	hl,bc
	add	hl,de		;compute result exponent
	ld	d,a		;save result sign
	ld	e,l		;save result exponent
	ld	a,h
	or	a,a		;high-order exponent zero?
	jr	z,expok		;- yes, skip

	cp	a,80H		;set carry if positive (overflow)
	sbc	hl,hl
	ld	e,h
	ld	a,0
	jr	exit1
expok:
	ld	hl,0
	push	hl		;initialize product area (IX-9)
	ld	bc,0

	;---------------------------------------

	ld	h, (ix-3)
	ld	l, (ix-6)
	mlt	hl		;..X x ..Y => 0EF
	ld	l,h
	ld	h,0		;HL = ..00E.

	;---------------------------------------

	ld	b, (ix-2)
	ld	c, (ix-6)
	mlt	bc		;.X. x ..Y
	add	hl,bc		;HL = ..XXX.

	ld	b, (ix-3)
	ld	c, (ix-5)
	mlt	bc		;..X x .Y.
	add	hl,bc		;HL = ..XXX.

	push	hl		;(IX-12)
	ld	hl,(ix-11)

	;---------------------------------------

	ld	b, (ix-1)
	ld	c, (ix-6)
	mlt	bc		;X.. x ..Y
	add	hl,bc		;HL = .XXXx.

	ld	b, (ix-2)
	ld	c, (ix-5)
	mlt	bc		;.X. x .Y.
	add	hl,bc		;HL = .XXXx.

	ld	b, (ix-3)
	ld	c, (ix-4)
	mlt	bc		;..X c Y..
	add	hl,bc		;HL = .XXXx.

	ld	a,l		;save for rounding
	ld	(ix-11),hl
	ld	hl,(ix-10)

	;---------------------------------------

	ld	b, (ix-1)
	ld	c, (ix-5)
	mlt	bc		;X.. x .Y.
	add	hl,bc		;HL = XXXxx.

	ld	b, (ix-2)
	ld	c, (ix-4)
	mlt	bc		;.X. x Y..
	add	hl,bc		;HL = XXXxx.

	ld	(ix-10),hl
	ld	hl,(ix-9)

	;---------------------------------------

	ld	b, (ix-1)
	ld	c, (ix-4)
	mlt	bc		;X.. x Y..
	add	hl,bc		;HL = XXxxx.

	ld	(ix-9),hl
	inc	sp
	inc	sp
	pop	hl

	ld	c,a
	ld	a,0
	sla	c
	adc	hl,hl
	adc	a,a
	sla	c
	adc	hl,hl
	adc	a,a
exit1:
	push	hl
	pop	bc
	ld	sp,ix
	call	__fppack
	pop	de
	pop	hl
	pop	ix
	ret

