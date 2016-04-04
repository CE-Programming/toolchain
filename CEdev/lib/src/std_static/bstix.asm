; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; byte store (ix+nnnnnn),A
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;                 A  : 8-bit integer to store
;
; Output:
;       none
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __bstix
__bstix:
        push    ix
        push    af              ; Preserve flags
        add     ix,bc
        pop     af              ; Restore flags
        ld      (ix),a
        pop     ix
        ret

