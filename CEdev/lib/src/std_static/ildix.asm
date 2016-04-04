; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer load hl,(ix+nnnnnn)
; Input:
;	Operand1: 
;                 BC : 24-bit offset from ix
;
; Output:
;	Result:   hl : 24 bit
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __ildix
__ildix:
        push    ix
        push    af              ; Preserve flags
        add     ix,bc
        pop     af              ; Restore flags
        ld      hl,(ix)
        pop     ix
        ret

