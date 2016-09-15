;************************************************************************
;*									*
;*		eZ80 Runtime Assembly Routine				*
;*									*
;*			Copyright 1993-2008 by				*
;*			      Zilog, Inc.				*
;*			     San Jose, CA 				*
;************************************************************************

	.assume adl=1
;	.def	_0_longjmp
;	.def	_1_longjmp
	.def	_longjmp

;--------------------------------------------------------------
;
;	  		longjmp
;
;
;  Prototype:	void longjmp(jmp_buf env,int val);
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

_longjmp       equ 000098h

;***************************************************************

;_longjmp:
;	push	ix
;	ld	ix,0
;	add	ix,sp
;	ld	iy,(ix+6)	; iy points to jmp_buf
;	ld	hl,_0_longjmp
;	ld	bc,(iy+0)
;	ld	(hl),bc		; save longjmp return address
;	ld	bc,(ix+3)	; bc contains return value
;	ld	hl,_1_longjmp
;	ld	(hl),bc
;	ld	bc,(iy+9)
;	ld	hl,_2_longjmp
;	ld	(hl),bc		; store old sp
;	ld	hl,(iy+6)	; hl has iy to restore
;	ld	ix,(iy+3)	; restore ix
;	ld	de,(iy+12)	; af in de
;	push	de
;	pop	af		; restore af
;	ld	bc,(iy+15)	; restore bc
;	ld	de,(iy+18)	; restore de
;	push	hl
;	ld	hl,(iy+21)	; restore hl
;	pop	iy
;	ld	sp,_2_longjmp	; Restore the stack pointer.
;	push	ix
;	ld	ix,0
;	add	ix,sp
;	push	hl
;	ld	hl,_1_longjmp	; get return value
;	ld	(ix+3),hl
;	ld	hl,_0_longjmp	; get return address
;	ld	(ix+0),hl
;	pop	hl
;	pop	ix
;
;	ret

;**************************** _longjmp ***************************

;; .FRAME _longjump,_seg__longjump,XDATA
;_0_longjmp:
;	DS 3
;_1_longjmp:
;	DS 3
;_2_longjmp:
;	DS 3

		end

