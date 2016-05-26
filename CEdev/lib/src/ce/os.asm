;-------------------------------------------------------------------------
; Call an OS or Bootcode routine
;-------------------------------------------------------------------------
	.assume ADL=1
	.def __OS

__OS:
	pop	de
	pop	hl
	push	hl
	push	de
	ld	iy,13631616
	jp	(hl)
	
	end