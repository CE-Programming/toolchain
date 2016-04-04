; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer store (ix+nnnnnn),HL
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;                 HL : 24-bit integer to store
;
; Output:
;       
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __istix
__istix:
        push    ix
        push    af              ; Preserve flags
        add     ix,bc
        pop     af              ; Restore flags
        ld      (ix),hl
        pop     ix
        ret

