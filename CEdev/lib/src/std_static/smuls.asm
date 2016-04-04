; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Multiply Signed
; Input:
;	Operand1: 
;		  bc : 16 bits
; 
;	Operand2: 
;		  hl :	 16 bits
;
; Output:
;	Result:   hl : 16 bits
;
; Registers Used:
;	
;-------------------------------------------------------------------------
	.assume adl=1
	.def	__smuls
	.ref	__imuls
__smuls:
	push	ix
	ld	ix,0
	add	ix,sp
	push	af
	push	bc
	ld	a,(ix-5)
	bit	7,a
	jr	z,_bcpos
	ld	a,FFH
	jr	_testhl
_bcpos:
	ld	a,0
_testhl:	
	ld	(ix-4),a
	pop	bc
	push	hl
	ld	a,(ix-5)
	bit	7,a
	jr	z,_hlpos
	ld	a,FFH
	jr	_callit
_hlpos:
	ld	a,0
_callit:	
	ld	(ix-4),a
	pop	hl
	pop	af
	call	__imuls
	pop 	ix
	ret	
