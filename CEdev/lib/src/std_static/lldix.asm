; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; long load e:hl,(ix+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;
; Output:
;       Result:   E:HL : 32 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __lldix
__lldix:
        push    ix
        push    af              ; Preserve flags
        add     ix,bc
        pop     af              ; Restore flags
        ld      hl,(ix)
        ld      e,(ix+3)
        pop     ix
        ret

