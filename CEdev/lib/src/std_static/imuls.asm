; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Multiplication Signed.
; Input:
;	Operand1: 
;		  BC : 24 bits
;
;	Operand2: 
;		  HL : 24 bits
;
; Output:
;	Result:   hl : 24 bit
; Registers Used:
;	de,af
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__imuls
__imuls:
	push	ix
	ld	ix,0
	add	ix,sp
	;; 
	;; Push multiplicands
	;;
	push	bc		; Saved Op1 (1-3)
	push	bc		; 4-6 (XYZ) Op1
	push	hl		; 7-9 (BCD) Op2
	push	hl		; Saved Op2 (10-12)
	;;
	;; Push working registers
	;;
	push	de		; 13-15
	push	af		; 16-18
	;;
	;; Check the sign
	;; 
	ld	a,(ix-7)	; HOB Op2
	xor	a,(ix-4)	; HOB Op1
	jp	p,__ssign
	;;
	;; Different signs
	;;
	xor	a,(ix-4)	; S-bit sign of Op2
	jp	m,__op2neg
	;;
	;; Op1 is negative
	;;
	ex	de,hl
	ld	hl,0
	or	a,a
	sbc	hl,bc
	ld	(ix-6),hl	; save positive version of Op1
	push	hl
	pop	bc
	ex	de,hl
	jp	__ustart
__op2neg:
	ld	de,0
	ex	de,hl		; put Op2 in de
	or	a,a
	sbc	hl,de
	ld	(ix-9),hl	; save positive version of Op2
	jp	__ustart
	;;
	;; same sign, but which?
	;; 
__ssign:
	xor	a,(ix-4)
	jp	p,__ustart
	;;
	;; both negative
	;;
	ex	de,hl		; save Op2 in de
	ld	hl,0
	or	a,a
	sbc	hl,bc
	ld	(ix-6),hl	; save positive version of Op1
	ld	bc,hl
	ex	de,hl
	jp	__op2neg
	;; 
	;; Calculate middle byte
	;;
__ustart:	
	ld	hl,0
	ld	l,(ix-8)
	ld	h,(ix-6)
	mlt	hl		; CZ
	ld	de,0
	ld	d,(ix-9)
	ld	e,(ix-5)
	mlt	de		; DY
	add	hl,de
	;;
	;; shift left 8 bits
	;; 
	ld	de,0
	push	de		; 19-21
	ld	(ix-19),h
	ld	(ix-20),l
	pop	hl
	;;
	;; Caluclate lowest byte
	;; 
	ld	e,(ix-9)
	ld	d,(ix-6)
	mlt	de		; DZ
	;;
	;; Add low order byte
	;; 
	add	hl,de
	;;
	;; Calculate highest order byte
	;;
	or	a,a		;  clear carry
	ld	d,(ix-7)
	ld	e,(ix-6)
	mlt	de		; BZ
	ld	c,(ix-8)
	ld	b,(ix-5)
	mlt	bc		; CY
	ex	de,hl
	adc	hl,bc		; BZ+CY
	ex	de,hl
	or	a,a
	ld	b,(ix-9)
	ld	c,(ix-4)
	mlt	bc		; DX
	ex	de,hl
	adc	hl,bc		; BZ+CY+DX
	;;
	;; Shift left 16 bits
	;;
	ld	bc,0
	push	bc		; 19-21
	ld	(ix-19),l
	pop	hl
	;;
	;; add low 24-bit (8 bit carry + 16 bits)
	;; 
	or	a,a
	adc	hl,de
	;;
	;; hl has results -- check signs
	;;
	ld	a,(ix-1)
	xor	a,(ix-10)
	jp	p,__popregs
	ld	de,0
	ex	de,hl
	or	a,a
	sbc	hl,de
__popregs:
	pop	af		; restore af
	pop	de		; restore de
	pop	bc		; discard Saved Op1
	pop	bc		; discard Op2
	pop	bc		; discard Saved Op2
	pop	bc		; restore Op1
	pop 	ix
	ret	
