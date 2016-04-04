; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; byte store (iy+nnnnnn),A
; Input:
;	Operand1: 
;                 BC : 24-bit offset from iy
;                 A  : 8-bit integer to store
;
; Output:
;       
;
; Registers Used:
;      
;-------------------------------------------------------------------------
	.assume adl=1
        .def    __bstiy
__bstiy:
        push    iy
        push    af              ; Preserve flags
        add     iy,bc
        pop     af              ; Restore flage
        ld      (iy),a
        pop     iy
        ret

