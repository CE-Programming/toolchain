;-------------------------------------------------------------------------
; void abort(void) function
; For use in CEmu; triggers an open  in the debugger
;-------------------------------------------------------------------------
	.def	_abort
	.ref	_exit
	.assume adl=1

_abort:
	ld	a,1
	ld	(0FFFFFFh),a
	jp	_exit