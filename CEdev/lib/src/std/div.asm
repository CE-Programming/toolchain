;	        Copyright 1992-2008 Zilog, Inc. 
;-------------------------------------------------------------------------
;   Div function
;
;	div_t div(int numer,int denom);
; 
;-------------------------------------------------------------------------
	.assume adl=1
	.def	_div
	.ref	__idivs
	.ref	__irems
	SEGMENT code
_div:
	push	af
	push	bc
	push	hl
	push    de

	ld hl,21
	add hl,sp
	ld bc,(hl) 		; bc=val of denominator
	dec hl
	dec hl
	dec hl
	ld hl,(hl) 		; hl=val of numerator
	push hl
	call __idivs
	ex de,hl 		; de= quotient
	pop hl			; hl=val of numerator
	call __irems
	ld bc,hl

	ld hl,15
	add hl,sp
	ld hl,(hl)
	inc hl
	inc hl
	inc hl
	ld (hl),bc		 ; remainder
	dec hl
	dec hl
	dec hl
	ld (hl),de 		;quotient

	pop	de
	pop	bc
	pop	bc
	pop af

	ret




