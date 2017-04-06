;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_RemoveAllBreakpoints
	.assume	adl=1

;--------------------------------------------------------------------
_RemoveAllBreakpoints:
; Sets a breakpoint at a particular address
; Arguments
;  HL = Address to set as breakpoint
	scf
	sbc	hl,hl
	ld	(hl),9
	ret
