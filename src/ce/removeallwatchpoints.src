;-------------------------------------------------------------------------
; For use in CEmu (And maybe other future emulators)
;-------------------------------------------------------------------------
	.def	_RemoveAllWatchpoints
	.assume	adl=1

;--------------------------------------------------------------------
_RemoveAllWatchpoints:
; Removes all the watchpoints
; Arguments
;  None
	scf
	sbc	hl,hl
	ld	(hl),10
	ret
