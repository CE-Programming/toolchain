; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; long store (ix+nnnnnn),H:HL
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;                 E:HL : 32-bit value
;
; Output:
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __lstix
__lstix:
        push    ix
        push    af              ; Preserve flags
        add     ix,bc
        pop     af              ; Restore flags
        ld      (ix),hl
        ld      (ix+3),e
        pop     ix
        ret

