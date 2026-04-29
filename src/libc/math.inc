.ifndef __MATH_INC__
	.set	__MATH_INC__, 1

; math.inc
; Assembly equates for libc <math.h>
; Remember to keep this file in sync with <math.h>

	; note that FP_ILOGBINF is INT_MAX
	.equ	FP_ILOGB0    , 0x800000
	.equ	FP_ILOGBNAN  , 0x7FFFFF

	.equ	FP_ZERO      , 0x0
	.equ	FP_INFINITE  , 0x1
	.equ	FP_SUBNORMAL , 0x2
	.equ	FP_NAN       , 0x3
	.equ	FP_NORMAL    , 0x4

.endif
