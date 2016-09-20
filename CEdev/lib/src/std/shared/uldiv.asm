; (c) Copyright 1999-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Long Division.
; Input:
;	Operand1: 
;		  (ix+9) : high word,high byte
;		  (ix+8) : high word,low byte
;		  (ix+7) : low word,high byte
;		  (ix+6) : low word,low byte
;
;	Operand2: 
;		  (ix+15) : high word,high byte
;		  (ix+14) : high word,low byte
;		  (ix+13) : low word,high byte
;		  (ix+12) : low word,low byte
;
; Output:
;	Result:   b : high byte
;		  de : low byte
; Registers Used:
;	a,b,c,d,e,h,l,iy
;-------------------------------------------------------------------------
	.assume adl=1
	.def	.uldiv

.uldiv:
	push	ix
	ld	ix,0
	add	ix,sp

	ld	de,0		;res = 0;
	ld	b,0		

	ld	hl,0		;num = 0
	ld	c,0		

	ld	iy,32		;i = 32;
	
loop:
				;res = res << 1
	ex	de,hl
	add	hl,hl
	ld	a,b
	adc	a,b
	ld	b,a
	ex	de,hl

				;num = num << 1
	add	hl,hl
	ld	a,c
	adc	a,c
	ld	c,a

				;x = x << 1
	ld	a,(ix+6)
	add	a,(ix+6)
	ld	(ix+6),a
	ld	a,(ix+7)
	adc	a,(ix+7)
	ld	(ix+7),a
	ld	a,(ix+8)
	adc	a,(ix+8)
	ld	(ix+8),a
	ld	a,(ix+9)
	adc	a,(ix+9)
	ld	(ix+9),a


	push	de

				;num = num + carry

	ld	de,0
	adc	hl,de
	ld	a,c
	adc	a,d
	ld	c,a


				;num = num - y
	ld	de,(ix+12)
	or	a,a
	sbc	hl,de
	ld	a,c
	ld	d,(ix+15)
	sbc	a,d
	ld	c,a

	pop	de
	jr	c, out		;if (num < y) goto out

	inc	de		;res = res | 1

	jr	done		;goto done

out:
	push 	de
				;num = num + y
	ld	de,(ix+12)
	add	hl,de
	ld	a,c
	ld	d,(ix+15)
	adc	a,d
	ld	c,a

	pop	de

done:
				;i--, if (i != 0) go to loop 
	dec 	iyl
	jr	nz,loop


	pop 	ix
	ret	

	.def	.uldivbdechl
.uldivbdechl:
	push	bc
	push	hl
	ld	c,b
	push	bc
	push	de
	call	.uldiv
	ld	iy,12
	add	iy,sp
	ld	sp,iy
	ret	
