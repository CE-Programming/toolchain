; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; byte load a,(iy+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;
; Output:
;       Result:   A : 8 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __bldiy
__bldiy:
        push    iy
        push    af      ; Preserve flags
        add     iy,bc
        pop     af      ; Restore flags
        ld      a,(iy)
        pop     iy
        ret

