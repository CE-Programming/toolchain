; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Multiply Signed/Unsigned
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1: 
;		  BC : 16 bits
; 
;	Operand2: 
;		  HL : 16 bits
;
; Output:
;	Result:   HL : 16 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.def __smulu,__smuls
	.assume adl=1

__smuls        equ 000224h
__smulu        equ 000228h

