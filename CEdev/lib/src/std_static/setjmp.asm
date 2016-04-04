;************************************************************************
;*									*
;*		eZ80 Runtime Assembly Routine				*
;*									*
;*			Copyright 1993-2008 by				*
;*			     Zilog, Inc.				*
;*			    San Jose, CA				*
;************************************************************************

	.assume adl=1
;	.def	_0_setjmp
	.def	_setjmp

;--------------------------------------------------------------
;
;	  		setjmp
;
;
;  Prototype:	int setjmp(jmp_buf env);
;
;  Buffer Layout:	pc	; return address
;			ix	
;			iy	; frame pointer.
;			sp	
;			af	
;			bc	
;			de	
;			hl	
;
;--------------------------------------------------------------

		SEGMENT CODE

_setjmp:
	ld iy,0
	add iy,sp
	ld hl,iy
	ld iy,(iy+3)	;get jmp_buf
	ld (iy+3),ix	;save ix
	ld (iy+6),hl	;save sp
	ld hl,(hl)
	ld (iy+0),hl	;save return adress
	ld hl,0
	ret

;*************************************************************


;_setjmp:
;	push	ix
;	ld	ix,0
;	add	ix,sp
;	push	iy
;	push	af
;	push	bc
;	push	de
;	push	hl
	;;
	;; Save address of jmp_buf
	;; 
;	ld	hl,_0_setjmp
;	ld	de,(ix+6)	; de points to jmp_buf
;	ld	(hl),de
;	ex	de,hl
;	ld	de,(ix+3)	; get return address
;	ld	(hl),de
;	inc	hl
;	inc	hl
;	inc	hl
;	ld	de,(ix+0)	; get ix
;	ld	(hl),de		; store in jmp_buf
;	inc	hl
;	inc	hl
;	inc	hl
;	ld	de,iy		; get iy
;	ld	(hl),de		; store
;	ld	iy,hl
;	lea	de,ix-3		; get old sp
;	ld	(iy+3),de
;	ld	de,(ix-3)	; get af
;	ld	(iy+6),de
;	ld	de,(ix-6)	; get bc
;	ld	(iy+9),de
;	ld	de,(ix-9)	; get de
;	ld	(iy+12),de
;	ld	de,(ix-12)	; get hl
;	ld	(iy+15),de
;	pop	hl
;	pop	de
;	pop	bc
;	pop	af
;	pop	iy
;	pop	ix
;	ret	
;**************************** _setjmp ***************************

		;; FRAME _setjmp,_seg__setjmp,XDATA
;_0_setjmp:
;	DS 3

		end

