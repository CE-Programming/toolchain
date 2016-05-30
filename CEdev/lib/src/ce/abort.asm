;-------------------------------------------------------------------------
; void abort(void) function
; For use in CEmu; triggers an open  in the debugger
;-------------------------------------------------------------------------
	.def	_abort
	.ref	_exit
	.assume adl=1

_abort:
	scf
	sbc	hl,hl
	ld	(hl),1
	jp	_exit