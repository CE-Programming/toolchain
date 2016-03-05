	.assume ADL=1
	.def _pgrm_CleanUp

; === Simple Cleanup =========================
_pgrm_CleanUp:
	push	iy
	ld	iy,%D00080
	call	%0020E5C ; DelRes
	call	%0020818 ; ClrTxtShd
	call	%0020814 ; ClrScrn
	call	%0020828 ; HomeUp
	call	%0021A3C ; DrawStatusBar
	set	0,(iy+3) ; graphDraw,(iy+graphFlags)
	pop	iy
	ret
; ============================================