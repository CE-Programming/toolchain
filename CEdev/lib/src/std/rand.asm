	.ref __lmulu
	.ref __ladd
	.ref __lshru
	.ref __land
	.def _rand
	.def __next
	.assume adl=1
	
; int rand(void);

	SEGMENT DATA
__next:
	dl	1

	SEGMENT CODE
_rand:
	ld	a,(__next+3)
	ld	e,a
	ld	a,65
	ld	hl,(__next)
	ld	bc,12996205
	call	__lmulu
	ld	bc,12345
	xor	a,a
	call	__ladd
	ld	(__next),hl
	ld	a,e
	ld	(__next+3),a
	push	hl
	pop	bc
	ld	l,16
	call	__lshru
	ld	e,a
	ld	hl,bc
	ld	bc,32767
	xor	a,a
	jp	__land