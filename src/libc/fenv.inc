.ifndef __FENV_INC__
	.set	__FENV_INC__, 1

; fenv.inc
; Assembly fenv equates for libc <fenv.h>
; Remember to keep this file in sync with <fenv.h>

	.equ	FE_DIVBYZERO_BIT  , 6
	.equ	FE_INEXACT_BIT    , 5
	.equ	FE_INVALID_BIT    , 4
	.equ	FE_OVERFLOW_BIT   , 3
	.equ	FE_UNDERFLOW_BIT  , 2

	.equ	FE_DIVBYZERO_MASK , 1 << FE_DIVBYZERO_BIT
	.equ	FE_INEXACT_MASK   , 1 << FE_INEXACT_BIT
	.equ	FE_INVALID_MASK   , 1 << FE_INVALID_BIT
	.equ	FE_OVERFLOW_MASK  , 1 << FE_OVERFLOW_BIT
	.equ	FE_UNDERFLOW_MASK , 1 << FE_UNDERFLOW_BIT

	.equ	FE_ALL_EXCEPT     , FE_DIVBYZERO_MASK | FE_INEXACT_MASK | FE_INVALID_MASK | FE_OVERFLOW_MASK | FE_UNDERFLOW_MASK

	.equ	FE_TONEAREST      , 0
	.equ	FE_TOWARDZERO     , 1
	.equ	FE_DOWNWARD       , 2
	.equ	FE_UPWARD         , 3

.endif
