; Encode a list of forward distances to bytes patched by _SetSmcBytes.
.macro setSmcBytes targets:vararg
	call	_SetSmcBytes
	.db	(.Lsmc_end\@ - .Lsmc_start\@) / 2
.Lsmc_start\@:
	.irp target, \targets
		.dw	\target - . - 2
	.endr
.Lsmc_end\@:
.endm

.macro setSmcBytesFast first, targets:vararg
	pop	de			; de = return vector
	ex	(sp), hl		; l = byte
	ld	a, l
	ld	hl, \first
	ld	c, (hl)
	ld	(hl), a
	.irp target, \targets
		ld (\target), a
	.endr
	ld	a, c			; a = old byte
	ex	de, hl			; hl = return vector
	jp	(hl)
.endm

.macro setSmcBytesInline targets:vararg
	.irp target, \targets
		ld (\target), a
	.endr
.endm

.macro setSmcWordsInline targets:vararg
	.irp target, \targets
		ld (\target), hl
	.endr
.endm
