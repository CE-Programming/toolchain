.macro compare_hl_zero
	add	hl,de
	or	a,a
	sbc	hl,de
.endm

.macro compare_auhl_zero
	compare_hl_zero
	jr	nz,.+3
	or	a,a
.endm

.macro compare_hl_de
	or	a,a
	sbc	hl,de
	add	hl,de
.endm

.macro compare_bc_zero
	push	hl
	sbc	hl,hl
	adc	hl,bc
	pop	hl
.endm
