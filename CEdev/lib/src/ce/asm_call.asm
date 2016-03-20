; (c) Copyright 2016 Matt Waltz
;-------------------------------------------------------------------------
; Call an OS or Bootcode routine
;-------------------------------------------------------------------------
	.assume ADL=1
	.def __ASM

__ASM:
	pop	de
	pop	hl
	push	hl
	push	de
	ld	iy,13631616
	jp	(hl)
	
	end