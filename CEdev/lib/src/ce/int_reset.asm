;-------------------------------------------------------------------------
; Resets interrupts back to OS expected values
;-------------------------------------------------------------------------

	.def	_int_reset
	.assume adl=1

;------ ResetInterrupts --------------------------------------------------------
_int_reset:
	ld	hl,_ir
	ld	de,0F00004h
	ld	bc,16
	ldir
	ret
_ir:	dw	1 | 10h | 1000h | 2000h, 0
	dw	0FFFFh, 0FFFFh
	dw	1 | 8 | 10h, 0
	dw	0, 0

	end