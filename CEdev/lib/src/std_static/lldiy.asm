; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; long load e:hl,(iy+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;
; Output:
;       Result:   E:HL : 32 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __lldiy
__lldiy:
        push    iy
        push    af              ; Preserve flags
        add     iy,bc
        pop     af              ; Restore flags
        ld      hl,(iy)
        ld      e,(iy+3)
        pop     iy
        ret

