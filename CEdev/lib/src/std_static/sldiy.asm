; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; short load hl,(iy+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;
; Output:
;       Result:   hl : 16-bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __sldiy
__sldiy:
        push    iy
        push    af              ; Preserve flags
        add     iy,bc
        pop     af              ; Restore flags
        ld      hl,(iy)
        pop     iy
        ret

