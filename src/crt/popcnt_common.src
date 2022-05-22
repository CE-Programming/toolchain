	assume	adl=1

	section	.text
	public	__popcnt_common_init_full
__popcnt_common_init_full:
	; Calculates a combined popcount of L and HLU.
	; Note the carry flag must be combined with A on return.
	;     I: L,HLU=values to popcount
	;     O: A-cf=8-popcount(L)-popcount(HLU), HLU=H, L=0
	ld	a, l

	public	__popcnt_common_init
__popcnt_common_init:
	; Same as above, but input is in A and HLU.

	; Input value in A is inverted into L since HLU bits will be subtracted,
	; calculating 8-popcount(A) to match the sign of accumulated bits.
	cpl
	ld	l, a
	; Subtract an additional factor of H to cancel it out,
	; since the code below is subtracting it by a factor of 0xFF.
	sub	a, h

	public	__popcnt_common_iter
__popcnt_common_iter:
	; Calculates a popcount accumulation.
	; Note the carry flag must be combined with A on return.
	;     I: HLU,L=values to popcount, A=current accumulation
	;     O: A-cf=A+popcount(L)-popcount(HLU)+H-L, HLU=H, L=0
	sub	a, h

	public	__popcnt_common_iter_adjusted
__popcnt_common_iter_adjusted:
	; Same as above, but an additional H is accumulated into A.
	; This is the same popcount technique as described in __bpopcnt,
	; but bits shifted out from HLU are additionally subtracted.
	add	hl, hl
	sbc	a, h
	add	hl, hl
	sbc	a, h
	add	hl, hl
	sbc	a, h
	add	hl, hl
	sbc	a, h
	add	hl, hl
	sbc	a, h
	add	hl, hl
	sbc	a, h
	add	hl, hl
	sbc	a, h
	; Sets the carry flag to the final bit from HLU, which the caller handles.
	add	hl, hl
	ret
