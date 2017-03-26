;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_SetReadWriteWatchpoint
	.assume	adl=1

;--------------------------------------------------------------------
_SetReadWriteWatchpoint:
; Sets a read/write watchpoint at a particular address
; Arguments
;  DE = Address to set as breakpoint
;   C = Length of watchpoint
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	scf
	sbc	hl,hl
	ld	(hl),7
	ret
