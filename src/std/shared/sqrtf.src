;--------------------------------------------------------------
;
;	  	IEEE Single precision square root
;		Copyright 2003-2008 Zilog, Inc.
;
;--------------------------------------------------------------
;
; INPUTS:
;	Operand1: 
;		  (stack) : 32 bit IEEE format
;
; OUTPUTS:
;	Result: 
;		  EuHL : 32 bit IEEE format result
;
; ALGORITHM:
;	This algorithm is very similar to that used for binary
;	division;  readers should be familiar with that
;	algorithm of repetitive compare/subtract, and shift.
;	This algorithm uses the same concepts, except that the
;	number compared/subtracted is 2*x+1, where 'x' is the
;	developing result.  Briefly, if 'y' is the input parameter,
;	and 'x' is the result developed (and subtracted out) so
;	far, then 'y - x^2' is the residual value.  If the residual
;	is greater than '2*x + 1', then we subtract that out,
;	and add one to x;  this means that the new residual is
;	'y - (x+1)^2'.  Repetitively applied with shifting, 'x^2'
;	approaches the value of 'y'.
;
; Registers Used:
;	AF,BC,D
;
;--------------------------------------------------------------
	.def _sqrtf
	.assume adl=1

_sqrtf		equ 000298h
